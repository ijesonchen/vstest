package main

import (
	"log"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")
	testTimedWait()
}
