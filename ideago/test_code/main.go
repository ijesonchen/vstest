package main

import (
	"log"
	"time"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")
	log.Println(time.Now())
}
