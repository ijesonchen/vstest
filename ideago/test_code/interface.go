package main

import (
	"log"
	"unsafe"
)

func testInterface() {
	type testStruct struct {
		Data1 [10]int
	}

	var x testStruct
	var y interface{}
	y = x
	log.Printf("size %d interface %d", unsafe.Sizeof(x), unsafe.Sizeof(y))
}
