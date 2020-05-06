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
	uint64_t i = 0;
	for (i = 0; i < siz; i++){
		printStr(pgo[i].p, pgo[i].l);
	}
}
*/
import "C"

import (
	"fmt"
	"log"
	"reflect"
	"strings"
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
	log.Println(pa)
	//	C.printStringArray(C.ulonglong(pa.Data), C.ulonglong(5), C.ulonglong(pa.Len))
}

type StrArr [2]string

func testStringArray2() {
	n := 4
	strs := make([]StrArr, n)
	for i := 0; i < 4; i++ {
		strs[i] = StrArr{fmt.Sprintf("key_%d", i), fmt.Sprintf("val_%d", i)}
	}
	pa := (*reflect.SliceHeader)(unsafe.Pointer(&strs))
	log.Println(pa)
	//	C.printStringArray(C.ulonglong(pa.Data), C.ulonglong(5), C.ulonglong(pa.Len*2))
}

func testStringNull() {
	var s string
	p := (*reflect.StringHeader)(unsafe.Pointer(&s))
	log.Println("nil: ", p.Data, p.Len)
	s = ""
	p = (*reflect.StringHeader)(unsafe.Pointer(&s))
	log.Println("blank: ", p.Data, p.Len)
}

func testIntArrJoin() {
	ia := []int{1, 2, 3, 4, 5}
	s1 := fmt.Sprint(ia)
	log.Printf("%q", s1)
	s2 := strings.Trim(s1, "[]")
	log.Printf("%q", s2)
	s3 := strings.Fields(s2) // or split
	s4 := strings.Join(s3, ",")
	log.Printf("%q", s4)

	log.Printf("%q", strings.Trim(fmt.Sprint(ia), "[]"))
}

func testStringSplitPart() {
	s := "check_point_user: 1587716566071467897194 k@v|-|..."
	v := strings.Split(s, " ")
	pos := strings.Index(s, v[1])
	s2 := s[pos+len(v[1])+1:]
	log.Printf("[%s]", s2)
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
