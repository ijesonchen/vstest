package main

import (
	"fmt"
	"log"

	tf "github.com/tensorflow/tensorflow/tensorflow/go"
)

func dnnPred() {
	conf := LoadConf()
	log.Printf("%+v", *conf)

	docEmb := loadDnnData(conf.DataPath)

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

	// cut
	const maxInput = 10
	if len(input) > 10 {
		input = input[:maxInput]
	}

	modInfo, err := loadModel(conf.TensorFlow.ModPath)
	if err != nil {
		log.Printf("load modPath %s error %v", conf.TensorFlow.ModPath, err)
		return
	}
	fmt.Println()
	fmt.Println()
	printModelV2(modInfo.Mod)

	//if len(conf.TensorFlow.Output)!=0{
	//	modInfo.OutputName = conf.TensorFlow.Output
	//	log.Printf("output adjust %s", modInfo.OutputName)
	//}
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

	log.Printf("output %d %T %v", len(output), output, output)

	for i, oneout := range output {
		val := oneout.Value()
		if i < 10 {
			log.Printf("value %d type: %T", i, val)
			switch val.(type) {
			case [][]float32:
				val := val.([][]float32)
				var dim int
				for j := range val {
					if j == 0 {
						dim = len(val[j])
						if i == 0 {
							log.Printf("==>out %v", val[j])
						}
					} else {
						if dim != len(val[j]) {
							log.Printf("dim not equal %d %d", dim, len(val[j]))
						}
					}
				}
				log.Printf("dim1 %d dim2 %d", len(val), dim)
			}
		}
	}
}
