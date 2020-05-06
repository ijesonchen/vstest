package main

import (
	"encoding/json"
	"log"
	"strconv"
)

func testJson() {
	s := "{\\\"Uid\\\":\\\"99430517\\\"}"
	log.Printf("%s", s)
	s2, err := strconv.Unquote("\"" + s + "\"")
	log.Printf("[%s][%s][%v]", s, s2, err)

	var d struct {
		Uid string
	}
	err = json.Unmarshal([]byte(s2), &d)
	log.Print(err, d.Uid)
}
