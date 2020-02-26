package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"time"

	"github.com/coocood/freecache"
)

func testCache() {
	// NewCache(size int)中的size参数是指buffer的字节数，不是容纳的对象数。
	// 没有定时清理函数。读取时判断超时则返回ErrNotFound。
	// Peek函数忽略TTL，不受超时影响。
	ttlsec := 1
	cacheSize := 1000000
	loop := 1000

	cache := freecache.NewCache(cacheSize)

	for i := 0; i < loop; i++ {
		data := []byte(fmt.Sprintf("data_%d", i))
		_ = cache.SetInt(int64(i), data, ttlsec)
	}

	var miss, got, fail int
	log.Println("read data")
	for i := 0; i < loop; i++ {
		_, err := cache.GetInt(int64(i))
		if err != nil {
			if err == freecache.ErrNotFound {
				miss++
			} else {
				fail++
			}
		} else {
			got++
		}
	}
	log.Printf("got %d miss %d fail %d", got, miss, fail)

	time.Sleep(time.Second + time.Millisecond*10)

	got = 0
	miss = 0
	fail = 0
	log.Println("peek data")
	for i := 0; i < loop; i++ {
		var bKey [8]byte
		binary.LittleEndian.PutUint64(bKey[:], uint64(i))
		_, err := cache.Peek(bKey[:])
		if err != nil {
			if err == freecache.ErrNotFound {
				miss++
			} else {
				fail++
			}
		} else {
			got++
		}
	}
	log.Printf("got %d miss %d fail %d", got, miss, fail)

	got = 0
	miss = 0
	fail = 0
	log.Println("expired data")
	for i := 0; i < loop; i++ {
		_, err := cache.GetInt(int64(i))
		if err != nil {
			if err == freecache.ErrNotFound {
				miss++
			} else {
				fail++
			}
		} else {
			got++
		}
	}
	log.Printf("got %d miss %d fail %d", got, miss, fail)
}
