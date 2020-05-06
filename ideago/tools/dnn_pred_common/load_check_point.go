package dnn_pred_common

import (
	"bufio"
	"bytes"
	"encoding/json"
	"log"
	"os"
)

func loadCheckPoint(path string) map[string]map[int64]CheckPoint {
	cp1, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return nil
	}
	cp1Buf := bufio.NewScanner(cp1)
	hashMap := make(map[string]map[int64]CheckPoint)

	for cp1Buf.Scan() {
		data := cp1Buf.Bytes()
		if len(data) == 0 {
			continue
		}
		// log.Println(string(data))
		var a CheckPoint
		jsonDec := json.NewDecoder(bytes.NewReader(data[:len(data)-1]))
		jsonDec.UseNumber()
		if err := jsonDec.Decode(&a); err == nil {
			// if err := json.Unmarshal(data[:len(data)-1], &a); err == nil {
			rid := a.Rid
			if _, ok := hashMap[rid]; !ok {
				hashMap[rid] = make(map[int64]CheckPoint)
			}
			hashMap[rid][a.Iid] = a
		} else {
			log.Println(err)
		}
	}
	return hashMap
}
