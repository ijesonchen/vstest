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

func printModelV2(model *tf.SavedModel) (input, output string) { // 占位符为输入 out的输出为无消费者
	for i, op := range model.Graph.Operations() {
		log.Printf("op %d t %q n %q in %d out %d dev %q", i, op.Type(), op.Name(), op.NumInputs(), op.NumOutputs(), op.Device())
		for j := 0; j < op.NumOutputs(); j++ {
			out := op.Output(j)
			name := out.Op.Name()
			shape, err := out.Shape().ToSlice()
			consumers := out.Consumers()
			log.Printf("  %d %q %v %v %v", j, name, shape, err, consumers)
			for k, consume := range consumers {
				log.Printf("   consume %d %v", k, consume.DataType())
			}

		}
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
