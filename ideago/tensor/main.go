package main

import (
	"log"
	"math"
	"os"

	tf "github.com/tensorflow/tensorflow/tensorflow/go"
)

func diff(d1, d2 float32) (ok bool) {
	const delta = 1e-5
	if d1 == 0 {
		if math.Abs(float64(d2)) > delta {
			return true
		}
	} else {
		if math.Abs(float64((d2-d1)/d1)) > delta {
			return true
		}
	}
	return
}

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Printf("version %v", tf.Version())

	target := "./"

	if len(os.Args) == 2 {
		target = os.Args[1]
	}

	bertPredV2(target)
}
