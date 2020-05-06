package main

import (
	"github.com/spaolacci/murmur3"
	"log"
	"strconv"
)

func MeanHash(v interface{}, max, min, num float32) string {
	var f float32
	var ok bool
	if f, ok = v.(float32); ok {
	} else if s, ok := v.(string); ok {
		if ft, err := strconv.ParseFloat(s, 32); err == nil {
			f = float32(ft)
		}
	}
	if f < min {
		return "-1"
	}
	if float64(f) > float64(max)-1e-6 {
		return strconv.FormatInt(int64(num-1), 10)
	}
	return strconv.FormatInt(int64((f-min)/(max-min)*num), 10)
}

func MeanHash2(f, max, min, num float32) string {
	return strconv.FormatInt(int64((f-min)/(max-min)*num), 10)
}

func mm3Hash(str string) (ret uint64) {
	ret1, ret2 := murmur3.Sum128([]byte(str))
	ret = (ret1 ^ ret2) & 0x03ffffffffffffff
	return
}
func testMeanHash() {
	// 79 24000 500 24000 23500 80
	var val float32
	val = 24000
	s := MeanHash(val, 24000, 500, 80)
	log.Println(s)
	var f, max float32
	f = 24000
	max = 24000
	if float64(f) > float64(max)-1e-6 {
		log.Println("??????????")
	}

	log.Printf("%v %v", max, max-1e-6)

	log.Printf("true? %t", val > val-1e-6)

	str := "i_st_3_min_normal_price" + s
	log.Println("79 ", str, mm3Hash(str))
	str = "i_st_3_min_normal_price80"
	log.Println("80 ", str, mm3Hash(str))
}
