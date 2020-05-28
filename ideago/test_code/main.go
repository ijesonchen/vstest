package main

import (
	"log"
	"net/http"
	_ "net/http/pprof"
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

	go func() {
		log.Println(http.ListenAndServe("localhost:9999", nil))
	}()

	testFinalizer2()
}
