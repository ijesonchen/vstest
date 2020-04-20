package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"reflect"
	"strconv"
	"strings"
)

type KV map[string][]uint64

func parseKV(fn string) (raw []KV) {
	allData, err := ioutil.ReadFile(fn)
	if err != nil {
		log.Printf("open file %s error %v", fn, err)
		return
	}
	jsonDatas := strings.Split(string(allData), "\n")
	raw = make([]KV, 0, len(jsonDatas))
	for _, j := range jsonDatas {
		if len(j) < 5 {
			continue
		}
		data := make(KV)
		j = strings.ReplaceAll(j, "u'", "'")
		j = strings.ReplaceAll(j, "'", "\"")
		//log.Println("===> ", j)
		err = json.Unmarshal([]byte(j), &data)
		if err != nil {
			log.Printf("parse error %v", err)
			continue
		}
		//log.Println("data: ", data)
		raw = append(raw, data)
	}
	log.Printf("read %d data", len(raw))
	return
}

func parseKVV2(fn string) (raw []KV) {
	allData, err := ioutil.ReadFile(fn)
	if err != nil {
		log.Printf("open file %s error %v", fn, err)
		return
	}
	lines := strings.Split(string(allData), "\n")
	raw = make([]KV, 0, len(lines))
	for _, line := range lines {
		if len(line) < 5 {
			continue
		}
		data := make(KV)
		items := strings.Split(line, "|-|")
		for _, item := range items {
			kvs := strings.Split(item, "@")
			if len(kvs) != 2 {
				log.Printf("parse error %v", item)
				continue
			}
			key := kvs[0]
			var vs []uint64
			vals := strings.Split(kvs[1], ",")
			for _, v := range vals {
				v = strings.TrimRight(v, "\x00")
				id, err := strconv.ParseUint(v, 10, 64)
				if err != nil {
					log.Printf("parse error %v %v", v, err)
				} else {
					vs = append(vs, id)
				}
			}
			if len(key) > 0 && len(vs) > 0 {
				data[key] = vs
			}
		}

		//log.Printf("===> [%s]", j)
		//log.Println("data: ", data)
		raw = append(raw, data)
	}
	log.Printf("read %d data", len(raw))
	return
}

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	hashfn1 := "hash1.txt"
	hashfn2 := "hash3.txt"
	kv1 := parseKV(hashfn1)
	kv2 := parseKVV2(hashfn2)
	log.Printf("read hash1 %d hash2 %d", len(kv1), len(kv2))
	if len(kv1) != len(kv2) {
		log.Printf("len not equal %d %d", len(kv1), len(kv2))
		return
	}
	miss := 0
	diff := 0
	total := 0
	for i := range kv1 {
		for k1, v1 := range kv1[i] {
			if v2, ok := kv2[i][k1]; !ok {
				miss++
				log.Printf("miss %d %s %v %v", i, k1, kv1[i][k1], kv2[i][k1])
				continue
			} else {
				if !reflect.DeepEqual(v1, v2) {
					log.Printf("diff %d %s %v %v", i, k1, v1, v2)
					diff++
				} else {
					total++
				}
			}
		}
	}
	log.Printf("total %d diff %d miss %d", total, diff, miss)
}
