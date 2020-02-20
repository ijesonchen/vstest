package main

import (
	"log"
	"sync"
)

/*
1. sync.Map无需初始化。Load后需要cast
*/

func testMap() {
	syncMap()
}

func syncMap() {
	var m sync.Map // 无需初始化
	m.Store("key", "test str")
	v, ok1 := m.Load("key")
	s, ok2 := v.(string)
	log.Printf("%v %v %q", ok1, ok2, s) // true true "test str"
}
