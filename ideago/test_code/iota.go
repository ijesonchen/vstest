package main

import "log"

const (
	iotaA1 = iota // 必须是const的第一行，才是从0开始
	iotaA2
	iotaA3
)

const (
	iotaB1 = 1 << iota
	iotaB2
	iotaB3
)

const (
	iotaC1 = 10
	iotaC2 = 18
	iotaC3 = iota // 第3行，对应2
)

func testIota() {
	log.Println(iotaA1, iotaA2, iotaA3)
	log.Println(iotaB1, iotaB2, iotaB3)
	log.Println(iotaC1, iotaC2, iotaC3)
}
