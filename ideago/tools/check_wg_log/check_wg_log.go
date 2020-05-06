package main

import (
	"bufio"
	"bytes"
	"log"
	"os"
)

func loadWgLog(path string) {
	cp1, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return
	}
	cp1Buf := bufio.NewScanner(cp1)

	wgdata := make(map[string]int)
	wgerr := make(map[string]int)
	tag := []byte("__debug WaitGroup")
	taglen := len(tag)

	for cp1Buf.Scan() {
		// E0505 14:56:59.255972  7650 thread_pool.hpp:29] __debug WaitGroup 2017082389 notify 0
		line := cp1Buf.Bytes()
		pos := bytes.Index(line, tag)
		if pos > 0 {
			line1 := line[pos+taglen+1:]
			wgs := bytes.Split(line1, []byte(" "))
			if len(wgs) != 3 {
				log.Printf("err parse %s", line1)
				continue
			}
			ret := 0
			switch string(wgs[1]) {
			case "add":
				ret = 1
			case "notify":
				ret = 2
			case "wait":
				ret = 4
			}
			wgdata[string(wgs[0])] += ret
			if string(wgs[2]) != "0" && ret != 1 {
				wgerr[string(wgs[0])] = 1
				log.Printf("error x %s", line1)
			}
		}
	}
	log.Println("================")
	for k, v := range wgdata {
		if v != 7 {
			log.Printf("err %s %d", k, v)
		}
	}
	log.Println("================")
	log.Printf("invalid x %v", wgerr)

}

func main() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
	log.Println("enter main")
	defer log.Println("leave main")

	loadWgLog("a1.log")

	log.Println("end main")
}
