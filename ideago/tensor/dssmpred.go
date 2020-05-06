package main

import (
	"fmt"
	"log"

	tf "github.com/tensorflow/tensorflow/tensorflow/go"
)

func dssmPred() {
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
	const maxInput = 1
	if len(input) > maxInput {
		input = input[:maxInput]
	}

	modInfo, err := loadModel(conf.TensorFlow.ModPath)
	if err != nil {
		log.Printf("load modPath %s error %v", conf.TensorFlow.ModPath, err)
		return
	}
	fmt.Println()
	fmt.Println()
	_, _, allLayers := printModelV2(modInfo.Mod)
	fmt.Println()
	fmt.Println()
	//layerNames := []string{
	//	"tower_0_test/tower_0/user_nn_l2_norm",
	//	"tower_0_test/tower_0/doc_nn_l2_norm",
	//	"tower_0_test/tower_0/Mul",
	//	"tower_0_test/tower_0/Sum",
	//	"tower_0_test/tower_0/mul_1",
	//	"tower_0_test/tower_0/Reshape_12",
	//	"tower_0_test/tower_0/softmax/Softmax",
	//}
	var layerNames []string
	for _, l := range allLayers {
		if l != modInfo.InputName {
			layerNames = append(layerNames, l)
		}
	}
	shapes := getModelShape(modInfo.Mod, layerNames)

	//if len(conf.TensorFlow.Output)!=0{
	//	modInfo.OutputName = conf.TensorFlow.Output
	//	log.Printf("output adjust %s", modInfo.OutputName)
	//}
	log.Printf("input %d shapes %v", len(input), shapes)

	for i := range input {
		log.Printf("input_data %s %v", ids[i], input[i])
	}

	inputTensor, err := tf.NewTensor(input)
	if err != nil {
		log.Printf("new tensor error %v", err)
		return
	}

	var fetches []tf.Output
	for _, o := range layerNames {
		fetches = append(fetches, modInfo.Mod.Graph.Operation(o).Output(0))
	}

	tensors, err := modInfo.Mod.Session.Run(
		map[tf.Output]*tf.Tensor{
			modInfo.Mod.Graph.Operation(modInfo.InputName).Output(0): inputTensor,
		},
		fetches,
		nil)
	if err != nil {
		log.Printf("session run error %v", err)
		return
	}

	log.Printf("output %d %T %v", len(tensors), tensors, tensors)

	if len(tensors) != len(layerNames) {
		log.Printf("session return invlaid %d - %d", len(layerNames), len(tensors))
		return
	}

	//outputs :=make([][][]float32, len(layerNames))
	outputsI := make([]interface{}, len(layerNames))

	for i, tensor := range tensors {
		tValue := tensor.Value()
		outputsI[i] = tValue
		//val, ok := tValue.([][]float32)
		//if !ok{
		//	log.Printf("invalid output %d %s %T", i, layerNames[i], tValue)
		//	continue
		//}
		//outputs[i]=val
	}

	log.Println()
	for i, o := range outputsI {
		log.Printf("%d %s %v", i, layerNames[i], o)
	}
	log.Println()

	//for i,o :=range outputs {
	//	log.Printf("%d %s %v", i, layerNames[i], o)
	//	for j, id :=range ids{
	//		log.Printf("%s %s %v", layerNames[i],id, o[j])
	//	}
	//}
}
