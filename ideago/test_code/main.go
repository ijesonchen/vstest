package main

import (
	"encoding/json"
	"log"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")

	k := map[int]int{1: 10, 2: 20, 3: 30}

	b, e := json.Marshal(k)
	log.Printf("%v %s %v", e, b, k)
}
