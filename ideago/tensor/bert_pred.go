package main

import (
	tf "github.com/tensorflow/tensorflow/tensorflow/go"
	"log"
	"math"
	"sync"
	"time"
)

func normF32(in []float32) (out []float32) {
	var t float32
	for _, i := range in {
		t += i * i
	}
	t = float32(math.Sqrt(float64(t)))
	for i := range in {
		in[i] /= t
	}
	return in
}
func bertPred(modPath string) {
	mod, err := loadModelV2(modPath)
	if err != nil {
		log.Printf("load modPath %s error %v", modPath, err)
		return
	}
	/*
		Model: "model_3"
		__________________________________________________________________________________________________
		Layer (type)                    Output Shape         Param #     Connected to
		==================================================================================================
		bert_x1_input (InputLayer)      (None, None)         0
		__________________________________________________________________________________________________
		bert_x2_input (InputLayer)      (None, None)         0
		__________________________________________________________________________________________________
		model_2 (Model)                 multiple             101332992   bert_x1_input[0][0]
		                                                                 bert_x2_input[0][0]
		__________________________________________________________________________________________________
		bert_lambda (Lambda)            (None, 768)          0           model_2[1][0]
		__________________________________________________________________________________________________
		dense_word_vector (Dense)       (None, 10)           7690        bert_lambda[0][0]
		==================================================================================================
	*/
	// input1:
	layerNames := []string{
		"bert_x1_input",
		"bert_x2_input",
		"non_masking_layer_1/Identity",
	}
	shapes := getModelShape(mod, layerNames)
	log.Printf("shapes %v", shapes)

	// 函湾四季女士韩版学院风甜美浅口短筒船袜10双  水果  手机
	toks := [][]int32{
		{101, 1141, 3968, 1724, 2108, 1957, 1894, 7506, 4276, 2110, 7368, 7599, 4494, 5401, 3840, 1366, 4764, 5030, 5670, 6154, 8108, 1352, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{101, 3717, 3362, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{101, 2797, 3322, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
	segs := [][]int32{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}

	log.Println(toks, segs)

	tToks, err := tf.NewTensor(toks)
	if err != nil {
		log.Printf("new tToks error %v", err)
		return
	}
	log.Printf("tToks:%v", tToks)

	tSegs, err := tf.NewTensor(segs)
	if err != nil {
		log.Printf("new tSegs error %v", err)
		return
	}
	log.Printf("tSegs:%v", tSegs)

	outLayerName := "non_masking_layer_1/Identity"
	layerNames2 := []string{"non_masking_layer_1/Identity"}
	var fetches []tf.Output
	fetches = append(fetches, mod.Graph.Operation(outLayerName).Output(0))

	log.Printf("out:%v", fetches)

	t0 := time.Now()
	tensors, err := mod.Session.Run(
		map[tf.Output]*tf.Tensor{
			mod.Graph.Operation("bert_x1_input").Output(0): tToks,
			mod.Graph.Operation("bert_x2_input").Output(0): tSegs,
		},
		fetches,
		nil)
	if err != nil {
		log.Printf("session run error %v", err)
		return
	}
	cost := time.Now().Sub(t0)

	log.Printf("output cost %v %d %T %v", cost, len(tensors), tensors, tensors)

	if len(tensors) != 1 {
		log.Printf("session return invlaid %d - %d", 1, len(tensors))
		return
	}

	//outputs :=make([][][]float32, len(layerNames))
	outputsI := make([]interface{}, len(layerNames2))
	var output [][]float32

	for i, tensor := range tensors {
		tValue := tensor.Value()
		outputsI[i] = tValue
		val, ok := tValue.([][]float32)
		if !ok {
			log.Printf("invalid output %T", tValue)
			continue
		}
		output = val
	}
	for i, o := range output {
		log.Printf("%d %v", i, normF32(o))
	}
}

func bertPredFunc(mod *tf.SavedModel, toks, segs [][]float32) (vecs [][]float32) {
	tToks, err := tf.NewTensor(toks)
	if err != nil {
		log.Printf("new tToks error %v", err)
		return
	}

	tSegs, err := tf.NewTensor(segs)
	if err != nil {
		log.Printf("new tSegs error %v", err)
		return
	}
	tensors, err := mod.Session.Run(
		map[tf.Output]*tf.Tensor{
			mod.Graph.Operation("bert_x1_input").Output(0): tToks,
			mod.Graph.Operation("bert_x2_input").Output(0): tSegs,
		},
		[]tf.Output{mod.Graph.Operation("non_masking_layer_1/Identity").Output(0)},
		nil)
	if err != nil {
		log.Printf("session run error %v", err)
		return
	}
	if len(tensors) != 1 {
		log.Printf("session return invlaid %d - %d", 1, len(tensors))
		return
	}

	for _, tensor := range tensors {
		tValue := tensor.Value()
		val, ok := tValue.([][]float32)
		if !ok {
			log.Printf("invalid output %T", tValue)
			continue
		}
		vecs = val
	}
	for _, o := range vecs {
		normF32(o)
	}
	return
}

func warmup(mod *tf.SavedModel, toks, segs [][]float32) {
	t0 := time.Now()
	bertPredFunc(mod, toks[:1], segs[:1])
	cost := time.Now().Sub(t0)
	log.Printf("warm up cost %v", cost)
}

func bertPredV2(modPath string) {
	mod, err := loadModelV2(modPath)
	if err != nil {
		log.Printf("load modPath %s error %v", modPath, err)
		return
	}

	// 函湾四季女士韩版学院风甜美浅口短筒船袜10双  水果  手机
	toks := [][]float32{
		{101, 1141, 3968, 1724, 2108, 1957, 1894, 7506, 4276, 2110, 7368, 7599, 4494, 5401, 3840, 1366, 4764, 5030, 5670, 6154, 8108, 1352, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{101, 3717, 3362, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{101, 2797, 3322, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
	segs := [][]float32{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}

	warmup(mod, toks, segs)

	t0 := time.Now()
	vecs := bertPredFunc(mod, toks, segs)
	cost := time.Now().Sub(t0)
	log.Printf("search 3 up cost %v", cost)
	for i, v := range vecs {
		log.Printf("%d %v", i, v)
	}

	t0 = time.Now()
	vecs = bertPredFunc(mod, toks[:1], segs[:1])
	cost = time.Now().Sub(t0)
	log.Printf("search 1 up cost %v", cost)
	for i, v := range vecs {
		log.Printf("%d %v", i, v)
	}

	loop := 1
	t0 = time.Now()
	var wg sync.WaitGroup
	for i := 0; i < loop; i++ {
		wg.Add(3)
		for j := 0; j < 3; j++ {
			go func(j int) {
				_ = bertPredFunc(mod, toks[j:j+1], segs[j:j+1])
				wg.Done()
			}(j)
		}
		wg.Wait()
	}
	cost = time.Now().Sub(t0)
	log.Printf("search1 %d up cost %v", loop, cost)

	t0 = time.Now()
	for i := 0; i < loop; i++ {
		for j := 0; j < 3; j++ {
			_ = bertPredFunc(mod, toks[j:j+1], segs[j:j+1])
		}
	}
	cost = time.Now().Sub(t0)
	log.Printf("search2 %d up cost %v", loop, cost)

	t0 = time.Now()
	for i := 0; i < loop; i++ {
		_ = bertPredFunc(mod, toks, segs)
	}
	cost = time.Now().Sub(t0)
	log.Printf("search3 %d up cost %v", loop, cost)

}
