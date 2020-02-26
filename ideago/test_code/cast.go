package main

import (
	"encoding/binary"
	"log"
	"math"
)

func testBitMoveAndUintCase() {
	// 1. 负数有符号数，case时二进制位可能会变化（要扩充符号位)
	//    所以a,b int32要按位组成c int64，必须经过等长uint变化后拼接，在转成int才不会导致二进制错误
	//    即 d:=uint32(a); e:=uint32(b), f := uint64(d)<<32 | uint64(e); c = int64(f)
	//    int32 -> uint64
	//    -1(ffffffff->ffffffffffffffff) math.MinInt32(80000000->ffffffff80000000)
	//    int32 -> uint32 -> uint64
	//    -1(ffffffff->00000000ffffffff) math.MinInt32(80000000->0000000080000000)
	// 2. 整型转换[]byte可使用binary.BigEndian.PutUint32()等函数。并且可以直观的看到二进制数据
	//    大端序和0x书写序相同。
	//    整型连续变化时，大端是尾部变化，小端是头部变化。

	buf := make([]byte, 8)

	var a, b int32
	a = -1
	binary.BigEndian.PutUint64(buf, uint64(uint32(a)))
	log.Printf("%x", buf) //
	a = math.MinInt32     //
	binary.BigEndian.PutUint64(buf, uint64(uint32(a)))
	log.Printf("%x", buf)
	b = a
	var c, f int64
	c = int64(a)<<32 + int64(b)    // 7fffffff80000000
	f = int64(a)<<32 | int64(b)    // -80000000
	g := uint64(a)<<32 | uint64(b) // ffffffff80000000
	d := int32(c >> 32)
	e := int32(c)
	h := int32(g >> 32)
	i := int32(g)
	log.Println(a == d, b == e, a == h, b == i) // 不一定正确
	log.Printf("%x %x %x", uint32(a), uint64(uint32(a)), uint64(uint32(a))<<32)
	log.Printf("%x %x %x", c, f, g)
	log.Printf("%x %x %x", int32(c>>32), int32(f>>32), int32(g>>32))
	log.Printf("%x %x %x %x %x %x %x", a, b, c, d, e, f, g)

	binary.LittleEndian.PutUint32(buf[:4], uint32(0x1234ffff)) // ffff3412
	binary.BigEndian.PutUint32(buf[4:], uint32(0x80001234))    // 80001234
	log.Printf("===> %x", buf)

	var x int32
	var y int64
	x = -1
	y = int64(x)
	log.Printf("%0x %0x", x, y)
}
