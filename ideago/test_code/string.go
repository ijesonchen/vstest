package main

/*
1. string赋值只拷贝指针和长度（StringHeader）
2.

*/

/*
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
// 所有字串长度为l, 字串数量为siz

struct GoStr{
	char* p;
	uint64_t l;
} GoStr;

void printStr(char*p, uint64_t l){
	char* p2 = (char*)malloc(l+1);
	memcpy(p2,p,l);
	p2[l]=0;
	printf("%s\n", p2);
	free(p2);
}

void printStringArray(uint64_t pi, uint64_t l, uint64_t siz){
	struct GoStr* pgo = (struct GoStr*)(pi);
	for (uint64_t i = 0; i < siz; i++){
		printStr(pgo[i].p, pgo[i].l);
	}
}
*/
import "C"

import (
	"fmt"
	"log"
	"reflect"
	"unsafe"
)

func printPtrString(k uintptr, l int) {
	sh := reflect.StringHeader{
		Data: k,
		Len:  l,
	}
	s := (*string)(unsafe.Pointer(&sh))
	log.Printf("%s", *s)
}

func strAssign() {
	s1 := fmt.Sprintf("string_data")
	s2 := s1
	p1 := (*reflect.StringHeader)(unsafe.Pointer(&s1))
	p2 := (*reflect.StringHeader)(unsafe.Pointer(&s2))
	log.Printf("s1 %x %d s2 %x %d", p1.Data, p1.Len, p2.Data, p2.Len)
}

func testStringArray() {
	n := 4
	strs := make([]string, n*2)
	for i := 0; i < 4; i++ {
		strs[i*2] = fmt.Sprintf("key_%d", i)
		strs[i*2+1] = fmt.Sprintf("val_%d", i)
	}
	pa := (*reflect.SliceHeader)(unsafe.Pointer(&strs))
	C.printStringArray(C.ulong(pa.Data), C.ulong(5), C.ulong(pa.Len))
}

type StrArr [2]string

func testStringArray2() {
	n := 4
	strs := make([]StrArr, n)
	for i := 0; i < 4; i++ {
		strs[i] = StrArr{fmt.Sprintf("key_%d", i), fmt.Sprintf("val_%d", i)}
	}
	pa := (*reflect.SliceHeader)(unsafe.Pointer(&strs))
	C.printStringArray(C.ulong(pa.Data), C.ulong(5), C.ulong(pa.Len*2))
}

func testStringNull() {
	var s string
	p := (*reflect.StringHeader)(unsafe.Pointer(&s))
	log.Println("nil: ", p.Data, p.Len)
	s = ""
	p = (*reflect.StringHeader)(unsafe.Pointer(&s))
	log.Println("blank: ", p.Data, p.Len)
}

func testString() {
	log.Println("===> testStringNull")
	testStringNull()
	log.Println("===> strAssign")
	strAssign()
	log.Println("===> testStringArray")
	testStringArray()
	log.Println("===> testStringArray2")
	testStringArray2()
}
