package main

import (
	"bufio"
	"bytes"
	"encoding/json"
	"log"
	"os"
	"reflect"
)

/*
{"id":[242819869104918869,29531891818007427,...],
"len":[1,1,1,1,...], "r_id":111111111, "iid":3803341, "score":0.00067748927},
*/

type cpOneline struct {
	Id    []uint64 `json:"id"`
	Len   []int    `json:"len"`
	Rid   string   `json:"r_id"`
	Iid   int64    `json:"iid"`
	Score float32  `json:"score"`
}

func main() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
	log.Println("comp checkpoint.txt and checkpoint1.txt and show diff")
	hashMap1 := getCpStruct("./checkpoint.txt")
	//hashMap2 := getCpStructV2("./checkpoint1.txt")
	hashMap2 := getCpStruct("./checkpoint1.txt")
	var count, total, req, identical, missreq, missitem int
	var missreqs []string
	missItems := make(map[string]int64)
	diffReqs := make(map[string]int)
	for rid, a := range hashMap1 {
		req++
		same := true
		ridh2, ok := hashMap2[rid]
		if !ok {
			missreq++
			missreqs = append(missreqs, rid)
			continue
		}
		for iid, b := range a {
			iidh2, ok := ridh2[iid]
			if !ok {
				missitem++
				missItems[rid] = iid
				continue
			}
			c := iidh2
			total++
			if !reflect.DeepEqual(b.idx, c.idx) {
				bSlot := make([]int, len(b.idx))
				var cursor int
				for s, l := range b.lenx {
					for i := 0; i < l; i++ {
						if cursor >= len(bSlot) {
							log.Println(rid, iid, b.idx, b.lenx)
							return
						}
						bSlot[cursor] = s
						cursor++
					}
				}

				cNum := len(c.idx)
				diffSlot := make(map[int]struct{})
				diffData := make(map[int][2]uint64)
				for i, h := range b.idx {
					if i < cNum && h != c.idx[i] {
						// log.Println(bSlot[i])
						// diffSlot = append(diffSlot, bSlot[i])
						diffSlot[bSlot[i]] = struct{}{}
						diffData[bSlot[i]] = [2]uint64{h, c.idx[i]}
					}
				}
				if len(diffSlot) != 0 {
					log.Println(rid, iid, diffSlot)
					log.Println(rid, iid, diffData)
					diffReqs[rid] = 1
				}
				count++
				same = false
			}
		}
		if same {
			identical++
		}
	}
	log.Printf("req %d identical %d miss %d missi %d total %d diff %d", req, identical, missreq, missitem, total, count)
	log.Printf("miss reqs %v", missreqs)
	log.Printf("miss items %v", missItems)
	var buf bytes.Buffer
	for k := range diffReqs {
		buf.WriteString(k)
		buf.WriteString(",")
	}
	log.Printf("diff reqs [%v]", buf.String())
}

type idInfo struct {
	idx  []uint64
	lenx []int
}

func getCpStruct(path string) map[string]map[int64]idInfo {
	cp1, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return nil
	}
	cp1Buf := bufio.NewScanner(cp1)
	hashMap := make(map[string]map[int64]idInfo)

	for cp1Buf.Scan() {
		data := cp1Buf.Bytes()
		if len(data) == 0 {
			continue
		}
		// log.Println(string(data))
		var a cpOneline
		jsonDec := json.NewDecoder(bytes.NewReader(data[:len(data)-1]))
		jsonDec.UseNumber()
		if err := jsonDec.Decode(&a); err == nil {
			// if err := json.Unmarshal(data[:len(data)-1], &a); err == nil {
			rid := a.Rid
			if _, ok := hashMap[rid]; !ok {
				hashMap[rid] = make(map[int64]idInfo)
			}
			hashMap[rid][a.Iid] = idInfo{a.Id, a.Len}
		} else {
			log.Println(err)
		}
	}
	return hashMap
}

func getCpStructV2(path string) (hashMap map[string]map[int64]idInfo) {
	cp1, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return nil
	}
	buf := bufio.NewScanner(cp1)
	hashMap = make(map[string]map[int64]idInfo)
	cpstr := []byte("cp_data:")
	cplen := len(cpstr)
	for buf.Scan() {
		data := buf.Bytes()
		if len(data) == 0 {
			continue
		}
		//log.Printf("%s", data)
		n := bytes.Index(data, cpstr)
		if n >= 0 {
			data = data[n+cplen:]
			var a cpOneline
			if err := json.Unmarshal(data, &a); err == nil {
				rid := a.Rid
				if _, ok := hashMap[rid]; !ok {
					hashMap[rid] = make(map[int64]idInfo)
				}
				hashMap[rid][a.Iid] = idInfo{a.Id, a.Len}
			} else {
				log.Println(err)
			}
		}
	}

	//
	//cpstr := "check_point:"
	//var buferr error
	//var line string
	//for    {
	//	if buferr != nil {
	//		if buferr == io.EOF {
	//			break
	//		}
	//		log.Printf("read file: %s error %v", path, buferr)
	//		return
	//	}
	//	line, buferr = buf.ReadString('\n')
	//	line = strings.TrimRight(line, "\r\n")
	//	if line == "" {
	//		continue
	//	}
	//	n := strings.Index(line, cpstr)
	//	if n>0{
	//		line = line[n+len(cpstr):]
	//		log.Println(line)
	//	}
	//
	//	var a cpOneline
	//	jsonDec := json.NewDecoder(bytes.NewReader(data[:len(data)-1]))
	//	jsonDec.UseNumber()
	//	if err := jsonDec.Decode(&a); err == nil {
	//		// if err := json.Unmarshal(data[:len(data)-1], &a); err == nil {
	//		rid := a.Rid.String()
	//		if _, ok := hashMap[rid]; !ok {
	//			hashMap[rid] = make(map[int64]idInfo)
	//		}
	//		hashMap[rid][a.Iid] = idInfo{a.Id, a.Len}
	//	} else {
	//		log.Println(err)
	//	}
	//}

	return
}
