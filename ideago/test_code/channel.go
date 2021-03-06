package main

import (
	"log"
	"math"
	"runtime"
	"time"
)

/*
 chan是多线程并发安全的
 chan读写可以导致STW，for range chan不会导致tight loop，不会影响gc
*/

func testChan2() {
	ch := make(chan bool)
	go func() {
		time.Sleep(time.Second * 3)
		close(ch)
	}()

	go func(sig chan bool) {
		log.Println("wait3")
		<-sig
		log.Println("end3")
	}(ch)

	log.Println("wait1")
	<-ch
	log.Println("end1")

	log.Println("wait2")
	<-ch
	log.Println("end2")
}

func testChan() {
	go func() {
		for {
			runtime.GC()
			time.Sleep(time.Millisecond * 100)
		}
	}()
	go func() {
		for {
			log.Println("**********************************")
			time.Sleep(time.Millisecond * 300)
		}
	}()
	time.Sleep(time.Second)
	go func() {
		sum := 1
		i := 0
		t0 := time.Now()
		for {
			i++
			sum += i
			if sum >= math.MaxInt32 {
				break
			}
			i--
		}
		log.Println("============================> tight exit", time.Now().Sub(t0))
	}()

	time.Sleep(time.Second)
}
