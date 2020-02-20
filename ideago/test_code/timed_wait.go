package main

import (
	"log"
	"sync"
	"time"
)

// just like sync.WaitGroup, but has TimedWait func
func testTimedWait() {
	var tw TimedWait
	tw.Add(1)

	log.Println("waiting...")
	tw.WaitSec(2)
	log.Println("done")
}

type TimedWait struct {
	wg sync.WaitGroup
	ch chan struct{}
}

func (t *TimedWait) Add(delta int) {
	t.wg.Add(delta)
}

func (t *TimedWait) Done() {
	t.wg.Done()
}

func (t *TimedWait) Wait() {
	t.wg.Wait()
}

func (t *TimedWait) TimedWait(duration time.Duration) (timedOut bool) {
	t.ch = make(chan struct{})
	go func() {
		defer func() {
			recover() // when timed out, chan is closed
		}()
		t.wg.Wait()
		t.ch <- struct{}{}
	}()

	timer := time.NewTimer(duration)
	select {
	case <-t.ch:
	case <-timer.C:
		timedOut = true
	}
	timer.Stop()
	close(t.ch)
	return
}

func (t *TimedWait) WaitSec(sec int) (timedOut bool) {
	return t.TimedWait(time.Duration(sec) * time.Second)
}
