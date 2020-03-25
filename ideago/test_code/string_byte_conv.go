package main

/*
var buf bytes.Buffer
1. buf.Bytes()可以直接修改buf的值（在buf未重新非配的情况下）
2. buf.String()会导致内存复制（buf可变，string不可变。[]byte到string会导致内存复制）
3. 不同类型指针间必须通过unsafe.Pointer转换。所以[]byte <-> string需要经过
*/

import (
	"bytes"
	"log"
	"reflect"
	"unsafe"
)

func testStringByteConv() {
	var buf bytes.Buffer
	buf.WriteString("this is a buffer")
	b1 := buf.Bytes()
	b1[0] = '*'
	s1 := buf.String()
	b1[1] = '*'
	ps1 := (*reflect.StringHeader)(unsafe.Pointer(&s1))
	ss1 := (*string)(unsafe.Pointer(ps1))
	pb1 := (*reflect.SliceHeader)(unsafe.Pointer(&b1))
	bb2 := *(*[]byte)(unsafe.Pointer(pb1))
	log.Printf("[%s] [%s]", *ss1, bb2)

}
