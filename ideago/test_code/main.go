package main

import (
	"log"
	"math"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")
	for i := 0; i < 5; i++ {
		log.Println(i, math.Ceil(float64(i*3)/float64(5)))
	}
}
