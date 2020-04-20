package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strings"
)

// json feature -> fea@val||xxx

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("convert test.txt(json) to test-encode.txt(key@val|-|...)")
	fn := "test.txt"
	allData, err := ioutil.ReadFile(fn)
	if err != nil {
		log.Printf("open file %s error %v", fn, err)
		return
	}
	jsonDatas := strings.Split(string(allData), "\n")
	raw := make([]map[string]string, 0, len(jsonDatas))
	for _, j := range jsonDatas {
		if len(j) < 5 {
			continue
		}
		data := make(map[string]string)
		err = json.Unmarshal([]byte(j), &data)
		if err != nil {
			log.Printf("parse error %v", err)
			continue
		}
		//log.Println("data: ", data)
		raw = append(raw, data)
	}
	log.Printf("read %d data", len(raw))

	output := "test-encode.txt"
	fOutput, err := os.OpenFile(output, os.O_RDWR|os.O_TRUNC|os.O_CREATE, 0666)
	if err != nil {
		log.Printf("create file %s error %v", output, err)
		return
	}
	for _, d := range raw {
		if len(d) == 0 {
			continue
		}
		i := 0
		for k, v := range d {
			if i > 0 {
				_, _ = fOutput.WriteString("|-|")
			}
			_, _ = fOutput.WriteString(fmt.Sprintf("%s@%s", k, v))
			i++
		}
		_, _ = fOutput.WriteString("\n")
	}
	fOutput.Close()
	log.Println("done")
}
