package main

import (
	"fmt"
	"log"

	tf "github.com/tensorflow/tensorflow/tensorflow/go"
)

type tfmodle struct {
	Mod        *tf.SavedModel
	InputName  string
	OutputName string
}

func printModel(model *tf.SavedModel) (input, output string) { // 占位符为输入 out的输出为无消费者
	for i, oneOp := range model.Graph.Operations() {
		log.Printf(fmt.Sprintln(i, oneOp.Name(), oneOp.NumInputs(), oneOp.NumOutputs(), oneOp.Type()))
		if "Placeholder" == oneOp.Type() {
			input = oneOp.Name()
		}
		for j := 0; j < oneOp.NumOutputs(); j++ {
			if 0 == len(oneOp.Output(j).Consumers()) {
				output = oneOp.Name()
			}
			for k, cum := range oneOp.Output(j).Consumers() {
				log.Printf("    %d out shape %s, %d consumer %s", j, oneOp.Output(j).Shape(), k, cum.Op.Name())
			}
		}
	}
	log.Printf("input %s output %s", input, output)
	return
}

func printModelV2(model *tf.SavedModel) (input, output string, layerNames []string) { // 占位符为输入 out的输出为无消费者
	for i, op := range model.Graph.Operations() {
		layerNames = append(layerNames, op.Name())
		log.Printf("op %d t %q n %q in %d out %d", i, op.Type(), op.Name(), op.NumInputs(), op.NumOutputs())
		for j := 0; j < op.NumOutputs(); j++ {
			out := op.Output(j)
			name := out.Op.Name()
			shape, err := out.Shape().ToSlice()
			consumers := out.Consumers()
			log.Printf("  %d %q %v %v %v", j, name, shape, err, consumers)
			for k, consume := range consumers {
				log.Printf("    consume %d %v", k, consume.Op.Name())
			}

		}
	}
	return
}

func getModelShape(model *tf.SavedModel, outputs []string) (shapes []int) {
	shapeMap := make(map[string]int, len(outputs))
	for _, o := range outputs {
		shapeMap[o] = -1
	}
	for i, op := range model.Graph.Operations() {
		//log.Printf("op %d t %q n %q in %d out %d dev %q", i, op.Type(), op.Name(), op.NumInputs(), op.NumOutputs(), op.Device())
		for j := 0; j < op.NumOutputs(); j++ {
			name := op.Output(j).Op.Name()
			if _, ok := shapeMap[name]; ok {
				shapes, err := op.Output(j).Shape().ToSlice()
				if err != nil {
					log.Printf("[%d]%q.[%d](%q) shape error %v", i, op.Name(), j, name, err)
					continue
				}
				if len(shapes) != 2 || shapes[1] <= 0 {
					log.Printf("[%d]%q.[%d](%q) shape invalid %v", i, op.Name(), j, name, shapes)
					continue
				}
				shapeMap[name] = int(shapes[1])
			}
		}
	}
	for _, o := range outputs {
		shapes = append(shapes, shapeMap[o])
	}
	return
}

func loadModel(modPath string) (*tfmodle, error) {
	model, err := tf.LoadSavedModel(modPath, []string{"serve"}, nil) // 需要tag
	if err != nil {
		return nil, err
	}
	input, output := printModel(model)

	// 找到输入、输出层

	return &tfmodle{Mod: model, InputName: input, OutputName: output}, nil
}

func loadModelV2(modPath string) (model *tf.SavedModel, err error) {
	model, err = tf.LoadSavedModel(modPath, []string{"serve"}, nil) // 需要tag
	if err != nil {
		return nil, err
	}
	return
}

func debugLoadModInfo(modPath string) {
	log.Println("tf version: ", tf.Version())

	modInfo, err := loadModel(modPath)
	if err != nil {
		log.Printf("load modPath %s error %v", modPath, err)
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

	log.Printf("shapes %v", shapes)
}
