package main

import (
	"log"
	"runtime"
	"sync"
	"time"
)

func testTightLoop() {
	go func() {
		for {
			runtime.GC()
			log.Println("gc forced")
			time.Sleep(time.Millisecond * 100)
		}
	}()

	time.Sleep(time.Millisecond * 200)

	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		log.Println("ENTER tight loop, gc will blocked in STW phase, check trace")
		t0 := time.Now()
		for i := 0; i < 3e9; i++ { // may cost 1sec
		}
		log.Println("LEAVE tight loop, cost", time.Now().Sub(t0))
		wg.Done()
	}()
	wg.Wait()
	time.Sleep(time.Millisecond * 300)
}
