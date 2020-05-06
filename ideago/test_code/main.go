package main

import (
	"fmt"
	"log"
	"net/http"
	_ "net/http/pprof"
	"reflect"
	"unsafe"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

type Response struct {
	ErrCode   int    `json:"code"`
	ErrDesc   string `json:"err_string"`
	Docs      []int  `json:"docs"`
	Props     string `json:"props"`
	RequestId string `json:"request_id"`
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")
	testStringSplitPart()

	go func() {
		log.Println(http.ListenAndServe("localhost:9999", nil))
	}()

	s := fmt.Sprintf("ttttt")
	s1 := s
	s2 := string([]byte(s))

	pfn := func(p *string) uintptr {
		return (*reflect.StringHeader)(unsafe.Pointer(p)).Data
	}
	log.Printf("%x %x %x", pfn(&s), pfn(&s1), pfn(&s2))
}
