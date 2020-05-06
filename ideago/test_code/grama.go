package main

import "log"

func testForSwitch() {
	log.Println("ENTER testForSwitch")
	for i := 0; i < 10; i++ {
		switch i {
		case 0:
			log.Printf("loop %d case %d", i, 1)
		case 1:
			log.Printf("loop %d case %d", i, 1)
		case 2:
			log.Printf("loop %d case %d", i, 2)
			continue // continue for loop
		case 3:
			log.Printf("loop %d case %d", i, 3)
			break // only break switch, will print "after switch 3"
		case 4:
			log.Printf("loop %d case %d", i, 4)
			fallthrough
		case 5:
			log.Printf("loop %d case %d", i, 5)
		default:
			log.Printf("should not got here")
		}
		log.Printf("after switch %d", i)
	}
	log.Println("LEAVE testForSwitch")
}
