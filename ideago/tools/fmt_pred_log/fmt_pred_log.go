package main

import (
	"encoding/json"
	"log"
	"os"
)

/*
console.log : id, len, iid, r_id
I0420 17:02:42.146481  4118 call_worker.cpp:111] cp_data: {"id":[46555936683421268,...],"iid":3803341,"len":[1,...],"r_id":"xxx"}
zero.log : score, embedding
{"level":"info","time":"2020-04-20T17:02:42+08:00","message":"check_point_feature: 111111111 score 3803341 0.0055497694 [3.1777453 ...]"}
*/

type cpData struct {
	Id    []uint64 `json:"id"`
	Len   []int    `json:"len"`
	Rid   string   `json:"r_id"`
	Iid   int64    `json:"iid"`
	Score float32  `json:"score"`
	//Embed []float32 `json:"embed"`
}

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("exec [con.log zero.log cp.txt]")

	conLogPath := "./data/console.log"
	zeroLogPath := "./data/zero.log"
	outPutPath := "./data/check-point.txt"

	if len(os.Args) == 4 {
		conLogPath = os.Args[1]
		zeroLogPath = os.Args[2]
		outPutPath = os.Args[3]
	}

	f, err := os.OpenFile(outPutPath, os.O_CREATE|os.O_RDWR|os.O_TRUNC, 0666)
	if err != nil {
		log.Printf("open file %s error %v", outPutPath, err)
		return
	}
	defer f.Close()

	data := loadConsoleLog(conLogPath)
	appendZeroLog(zeroLogPath, data)

	for _, v1 := range data {
		for _, v2 := range v1 {
			b, err := json.Marshal(v2)
			if err != nil {
				log.Printf("marshal %+v error %v", v2, err)
				continue
			}
			_, err = f.Write(b)
			if err != nil {
				log.Printf("write %s error %v", outPutPath, err)
			}
			_, err = f.WriteString(",\n")
			if err != nil {
				log.Printf("write %s error %v", outPutPath, err)
			}
		}
	}

}
