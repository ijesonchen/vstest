package main

import (
	"log"

	tf "github.com/tensorflow/tensorflow/tensorflow/go"
)

/*

0 tower_0/W1 0 1 Const
    0 out shape [700, 500], 0 consumer tower_0_test/tower_0/MatMul_1
1 tower_0/B0 0 1 Const
    0 out shape [700], 0 consumer tower_0_test/tower_0/add_1
2 tower_0_test/tower_0/softmax/Reshape/shape 0 1 Const
    0 out shape [2], 0 consumer tower_0_test/tower_0/softmax/Reshape
3 tower_0/B2 0 1 Const
    0 out shape [2], 0 consumer tower_0_test/tower_0/add_3
4 tower_0/W0 0 1 Const
    0 out shape [440, 700], 0 consumer tower_0_test/tower_0/MatMul
5 tower_0/W2 0 1 Const
    0 out shape [500, 2], 0 consumer tower_0_test/tower_0/MatMul_2
6 tower_0/B1 0 1 Const
    0 out shape [500], 0 consumer tower_0_test/tower_0/add_2
7 tower_0_test/tower_0/embed_input 0 1 Placeholder
    0 out shape ?, 0 consumer tower_0_test/tower_0/MatMul
8 tower_0_test/tower_0/MatMul 2 1 MatMul
    0 out shape [?, 700], 0 consumer tower_0_test/tower_0/add_1
9 tower_0_test/tower_0/add_1 2 1 Add
    0 out shape [?, 700], 0 consumer tower_0_test/tower_0/Relu
10 tower_0_test/tower_0/Relu 1 1 Relu
    0 out shape [?, 700], 0 consumer tower_0_test/tower_0/MatMul_1
11 tower_0_test/tower_0/MatMul_1 2 1 MatMul
    0 out shape [?, 500], 0 consumer tower_0_test/tower_0/add_2
12 tower_0_test/tower_0/add_2 2 1 Add
    0 out shape [?, 500], 0 consumer tower_0_test/tower_0/Relu_1
13 tower_0_test/tower_0/Relu_1 1 1 Relu
    0 out shape [?, 500], 0 consumer tower_0_test/tower_0/MatMul_2
14 tower_0_test/tower_0/MatMul_2 2 1 MatMul
    0 out shape [?, 2], 0 consumer tower_0_test/tower_0/add_3
15 tower_0_test/tower_0/add_3 2 1 Add
    0 out shape [?, 2], 0 consumer tower_0_test/tower_0/softmax/Reshape
16 tower_0_test/tower_0/softmax/Reshape 2 1 Reshape
    0 out shape [?, 2], 0 consumer tower_0_test/tower_0/softmax/Softmax
17 tower_0_test/tower_0/softmax/Softmax 1 1 Softmax
input tower_0_test/tower_0/embed_input output tower_0_test/tower_0/softmax/Softmax
*/
func testLoadAndEval() {
	// load mod, load data, eval, check: passed.
	modPath := "./data"
	logPath := "./data/zero.log"

	docEmb := loadDnnData(logPath)

	var nEmbedSize int
	for _, v := range docEmb {
		if nEmbedSize == 0 {
			nEmbedSize = len(v.input)
		} else {
			if nEmbedSize != len(v.input) {
				log.Printf("invalid embedding size %d %d", nEmbedSize, len(v.input))
				return
			}
		}
	}

	var ids []string
	var input [][]float32
	var scores []float32
	for k, v := range docEmb {
		ids = append(ids, k)
		input = append(input, v.input)
		scores = append(scores, v.score)
	}

	modInfo, err := loadModel(modPath)
	if err != nil {
		log.Printf("load modPath %s error %v", modPath, err)
		return
	}

	log.Printf("input %d", len(input))

	inputTensor, err := tf.NewTensor(input)
	if err != nil {
		log.Printf("new tensor error %v", err)
		return
	}

	output, err := modInfo.Mod.Session.Run(
		map[tf.Output]*tf.Tensor{
			modInfo.Mod.Graph.Operation(modInfo.InputName).Output(0): inputTensor,
		},
		[]tf.Output{
			modInfo.Mod.Graph.Operation(modInfo.OutputName).Output(0),
		},
		nil)
	if err != nil {
		log.Printf("session run error %v", err)
		return
	}

	log.Printf("output %T %v", output, output)

	var score []float32
	for i, oneout := range output {
		val := oneout.Value()
		if i == 0 {
			log.Printf("value %d type: %T", i, val)
		}
		switch v := val.(type) {
		case [][]float32:
			score = make([]float32, len(v))
			for i, hitNohitScore := range v {
				score[i] = hitNohitScore[0] // 异常越界处理
			}
		case []float32:
			score = v
		}
	}
	var nDiff int
	for i := range score {
		if diff(score[i], scores[i]) {
			nDiff++
			if nDiff < 10 {
				log.Printf("diff %f %f", score[i], scores[i])
			}
		}
	}
	log.Printf("total %d diff %d", len(score), nDiff)
	//log.Printf("score  %v", score)
	//log.Printf("scores %v", scores)
}
