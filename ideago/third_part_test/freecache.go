package main

import (
	"encoding/binary"
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
	//testFreeCacheInt()
	//testFreeCacheByte()
	//testFreeCacheRand1()
	//testFreeCacheRand2()

	// key过多时，可能覆盖之前的key。但是一定可以取到对的数据。因为key也被保存了。
	//testFreeCacheInt2()

	// NewCache(size int)中的size参数是指buffer的字节数，不是容纳的对象数。
	// 没有定时清理函数。读取时判断超时则返回ErrNotFound。
	// Peek函数忽略TTL，不受超时影响。
	// testFreeCacheNewAndTTL()

	// 数据写满时，会淘汰掉旧的数据
	testFreeCacheOverWrite()
	// 一个数据至少占用header(24)+key+data。其中data至少1个字节
	// setint的key为8字节，所以一个数据至少33字节
	testFreeCacheEvacuate()
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

func testFreeCacheNewAndTTL() {
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

func testFreeCacheOverWrite() {
	ttl := 0                 // no expire
	cacheSize := 1000 * 1000 // key在 0-1M/0-100K范围内时 大约能存23K左右

	// 0 25006
	var key1 int64 = 0
	data1 := []byte("data_0")
	var key2 int64 = 25006
	data2 := []byte("data_25006")

	cache := freecache.NewCache(cacheSize)

	log.Print("=============")
	err := cache.SetInt(key1, data1, ttl)
	log.Printf("set %v err %v", key1, err)
	b, err := cache.GetInt(key1)
	log.Printf("get %v data %s err %v", key1, b, err)

	for i := 0; i < 1e6; i++ {
		data := []byte(fmt.Sprintf("data_%d", i))
		_ = cache.SetInt(int64(i), data, ttl)
	}

	log.Print("=============")
	err = cache.SetInt(key2, data2, ttl)
	log.Printf("set %v err %v", key2, err)
	b, err = cache.GetInt(key2)
	log.Printf("get %v data %s err %v", key1, b, err)

	log.Print("=============")
	b, err = cache.GetInt(key1)
	log.Printf("get %v data %s err %v", key1, b, err)

	log.Print("=============")
	b, err = cache.GetInt(key2)
	log.Printf("get %v data %s err %v", key1, b, err)
}

func testFreeCacheEvacuate() {
	ttl := 0          // no expire
	cacheSize := 8448 // key在 0-1M/0-100K范围内时 大约能存23K左右

	// 0 25006
	//var key1 int64 = 0
	//data1 := []byte("data_0")
	//var key2 int64 = 25006
	//data2 := []byte("data_25006")

	cache := freecache.DebugNewCacheCustomTimer(cacheSize)

	data := []byte("aaaaaaaaaaaaaaaaaaaaaaaa")
	for i := 0; i < 1e6; i++ {
		_ = cache.SetInt(int64(i), data, ttl)
	}

	log.Printf("entry %d evacuate %d", cache.EntryCount(), cache.EvacuateCount())
	cache.DebugEntryCount()
	for i := 0; i < 1e6; i++ {
		if i%2 == 0 {
			_ = cache.SetInt(int64(i), nil, ttl)
		} else {
			_ = cache.SetInt(int64(i), data, ttl)
		}
	}

	log.Printf("entry %d evacuate %d", cache.EntryCount(), cache.EvacuateCount())
	cache.DebugEntryCount()

}
