package main

import (
	"log"
	"sync"
)

func testMap() {
	syncMap()
}

func syncMap() {
	var m sync.Map
	m.Store("key", "test str")
	log.Println(m.Load("key"))
}
