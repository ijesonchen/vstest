package main

import (
	"log"
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
	testString2Cstring()
}
