package main

import (
	"log"
	"strconv"
)

/*
1. slice传值调用。但是本身是类指针类型，所以在函数中可能修改入参。
2. 因为slice可以自动扩展长度，所以函数中修改过程可能导致slice变化。
3. 一般如果要对slice进行修改的函数，返回值中会包括这个slice。典型用法如append函数
*/

func testSlice() {
	testFillSlice1()
	testFillSlice2()
}

func testFillSlice1() {
	len := 10
	is := make([]int, len)
	fillSliceInt(is)
	ss := make([]string, len)
	fillSliceStr(ss)
	log.Printf("is %v", is)
	log.Printf("ss %v", ss)
}

func fillSliceInt(data []int) {
	for i := range data {
		data[i] = i
	}
}

func fillSliceStr(data []string) {
	for i := range data {
		data[i] = "s" + strconv.Itoa(i)
	}
}

func testFillSlice2() {
	len := 10
	is := make([]int, len)
	fillSliceInt(is)
	log.Printf("is fill %v", is)
	is2 := expandSliceInt(is)
	log.Printf("is origin %v", is)
	log.Printf("is2 expand %v", is2)
}

func expandSliceInt(data []int) []int {
	n := len(data)
	for i := 0; i < n; i++ {
		data = append(data, i+n)
	}
	return data
}
