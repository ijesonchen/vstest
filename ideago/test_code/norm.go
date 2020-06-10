package main

import (
	"log"
	"math"
)

func normF32(in []float32) (out []float32) {
	var t float32
	for _, i := range in {
		t += i * i
	}
	t = float32(math.Sqrt(float64(t)))
	out = make([]float32, len(in))
	for i := range out {
		out[i] = in[i] / t
	}
	return
}

func testNorm() {
	data := [][]float32{
		{187.8275, 91.5828, 47.9971, 41.5277, 45.8306, 37.5275, 41.6882, 226.231, 30.509, 124.766},
		{34.0835, 12.8879, 88.9141, 44.0651, 34.7776, 18.2538, 64.5216, 136.4224, 2.7925, 59.7186},
		{83.5521, 12.5714, 46.2534, 164.4664, 149.0879, 159.2491, 13.9158, 40.8224, 85.3831, 80.1614},
	}
	for i, d := range data {
		log.Printf("%d %v", i, normF32(d))
	}
}
