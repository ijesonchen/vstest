package dnn_pred_common

import (
	"bufio"
	"bytes"
	"encoding/json"
	"log"
	"os"
)

func LoadConsoleLog(path string) (hashMap map[string]map[int64]*CheckPoint, idMap map[string][]int64) {
	cp1, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return
	}
	buf := bufio.NewScanner(cp1)
	hashMap = make(map[string]map[int64]*CheckPoint)
	idMap = make(map[string][]int64)
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
			var a CheckPoint
			if err := json.Unmarshal(data, &a); err == nil {
				rid := a.Rid
				if _, ok := hashMap[rid]; !ok {
					hashMap[rid] = make(map[int64]*CheckPoint)
				}
				hashMap[rid][a.Iid] = &a
				idMap[rid] = append(idMap[rid], a.Iid)
			} else {
				log.Println(err)
			}
		}
	}
	return
}
