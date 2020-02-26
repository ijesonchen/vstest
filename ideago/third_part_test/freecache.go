package main

import (
	"fmt"
	"log"
	"math/rand"
	"strconv"
	"time"

	"github.com/coocood/freecache"
)

func testFreeCache() {
	// 1M key, 实际存储量：连续整形23K,连续整形字串24K，随机32位整形20K，随机64位整形18K。
	// 推测由于hash原因，一般空间利用率只有20%
	// 这个是不是示例中设置debug.SetGCPercent(20)的原因？
	testFreeCacheInt()
	testFreeCacheByte()
	testFreeCacheRand1()
	testFreeCacheRand2()

	// key过多时，可能覆盖之前的key。但是一定可以取到对的数据。因为key也被保存了。
	testFreeCacheInt2()
}

func testFreeCacheInt() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右
	input := cacheSize
	lookup := input

	cache := freecache.NewCache(cacheSize)
	var inErr, lookErr, got int
	for i := 0; i < input; i++ {
		data := []byte(fmt.Sprintf("data_%d", i))
		err := cache.SetInt(int64(i), data, ttl)
		if err != nil {
			inErr++
		}
	}
	time.Sleep(time.Millisecond * 10)
	log.Println("entry", cache.EntryCount())
	var ret []int
	for i := 0; i < lookup; i++ {
		_, err := cache.GetInt(int64(i))
		if err != nil {
			lookErr++
		} else {
			got++
			ret = append(ret, i)
		}
	}
	log.Printf("inerr %d out err %d got %d", inErr, lookErr, got)
	//log.Println(ret)
}

func testFreeCacheInt2() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右
	input := cacheSize
	lookup := input

	cache := freecache.NewCache(cacheSize)
	var inErr, lookErr, got int
	for i := 0; i < input; i++ {
		data := []byte(fmt.Sprintf("data_%d", i))
		err := cache.SetInt(int64(i), data, ttl)
		if err != nil {
			inErr++
		}
	}
	time.Sleep(time.Millisecond * 10)
	log.Println("entry", cache.EntryCount())
	var ret []int
	var keyerr int
	for i := 0; i < lookup; i++ {
		data, err := cache.GetInt(int64(i))
		if err != nil {
			lookErr++
		} else {
			got++
			s := fmt.Sprintf("data_%d", i)
			if s != string(data) {
				keyerr++
			}
			if rand.Float32() < 0.0001 {
				log.Printf("key %d %s", i, data)
			}
			ret = append(ret, i)
		}
	}
	log.Printf("inerr %d out err %d got %d keyErr %d", inErr, lookErr, got, keyerr)
	//log.Println(ret)
}
func testFreeCacheByte() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右
	input := cacheSize
	lookup := input

	cache := freecache.NewCache(cacheSize)
	var inErr, lookErr, got int
	for i := 0; i < input; i++ {
		key := strconv.Itoa(i)
		data := []byte(fmt.Sprintf("data_%d", i))
		err := cache.Set([]byte(key), data, ttl)
		if err != nil {
			inErr++
		}
	}
	time.Sleep(time.Millisecond * 10)
	log.Println("entry", cache.EntryCount())
	var ret []int
	for i := 0; i < lookup; i++ {
		key := strconv.Itoa(i)
		_, err := cache.Get([]byte(key))
		if err != nil {
			lookErr++
		} else {
			got++
			ret = append(ret, i)
		}
	}
	log.Printf("inerr %d out err %d got %d", inErr, lookErr, got)
	//log.Println(ret)
}

func testFreeCacheRand1() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右
	input := cacheSize

	cache := freecache.NewCache(cacheSize)
	var inErr int
	m := make(map[int32]bool)
	for i := 0; i < input; i++ {
		d := rand.Int31()
		m[d] = true
		key := fmt.Sprintf("%d_%d", rand.Int31(), 6009)
		data := []byte(fmt.Sprintf("data_%d", i))
		err := cache.Set([]byte(key), data, ttl)
		if err != nil {
			inErr++
		}
	}
	time.Sleep(time.Millisecond * 10)
	log.Printf("rand1 key %d entry %d", len(m), cache.EntryCount())
}

func testFreeCacheRand2() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右
	input := cacheSize

	cache := freecache.NewCache(cacheSize)
	var inErr int
	m := make(map[int]bool)
	for i := 0; i < input; i++ {
		d1 := rand.Int31()
		d2 := rand.Int31()
		d := int(d1)<<32 + int(d2)
		m[d] = true
		key := fmt.Sprintf("%d_%d", d1, d2)
		data := []byte(fmt.Sprintf("data_%d", i))
		err := cache.Set([]byte(key), data, ttl)
		if err != nil {
			inErr++
		}
	}
	time.Sleep(time.Millisecond * 10)
	log.Printf("rand2 key %d entry %d", len(m), cache.EntryCount())
}
