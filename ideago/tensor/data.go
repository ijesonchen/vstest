package main

import (
	"bufio"
	"encoding/json"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
)

/*
{"level":"info","time":"2020-04-17T10:41:21+08:00","message":"check_point_feature: 1587091280694216153983 score 40566546 0.0038456554 [3.0879004 1.0358167 -0.77182996 -1.5599546 2.146369 -0.6988194 0.72546697 2.894236 0.5083294 1.725839 -1.3083583 2.1488888 -1.4720389 1.0335916 -0.98792785 -1.5731629 1.753144 0.49346134 0.15055475 -1.4361278 1.2386411 -0.67611927 -0.9931327 0.86417633 1.3200343 0.17201194 -0.13204086 0.396031 -0.89023274 1.1838167 0.0893995 0.6875216 -0.112392336 -0.56487477 -0.16348773 0.34753335 0.45605764 -0.4270699 -0.10101405 0.30745867 1.3036318 1.5246344 1.742355 -3.1184905 -1.3813614 -0.6495865 -0.9345425 -0.5296342 0.57434756 2.0661564 -0.096288666 -0.7082655 -0.9268927 -0.11432314 0.95413816 1.752881 0.72308755 0.013528508 1.508878 0.9275212 0.39749727 1.0847877 1.2904817 -0.27116054 -1.3541859 -0.44610915 -0.54377764 0.61935925 1.1434125 -0.08710078 -0.19299632 -0.18819362 -0.09152181 0.06473294 -0.3027597 -0.30968902 -0.2802196 0.209875 -0.19651306 0.04238954 0.0048644077 -3.297081 -3.6220489 1.4544818 -0.02979535 1.4562728 -3.5336523 -3.2348638 3.4884028 0.0154043585 -1.0778303 1.4201518 -0.12632681 0.44689572 -0.12741894 0.9491131 -0.56114674 -1.371296 -0.4216261 -0.028044088 0.7421759 0.17112273 -0.7084914 -0.58029824 -0.83155423 -0.538446 0.19142938 1.2806475 -0.34814778 -1.5887159 0.3014459 0.2652299 -1.3312467 0.5792257 0.72564167 0.21163943 0.040616192 -0.188793 0.17247924 -0.9952135 1.3990176 -3.472054 -20.527195 28.681768 2.179209 -3.087293 0.50192994 7.3122315 6.240801 -24.111246 1.8753717 -2.9586167 -0.16705538 11.741592 -5.332058 2.2817304 -2.3981893 -17.083048 1.3211265 8.435169 -0.1259286 -0.5112749 -0.20080802 0.07388447 1.1476885 -0.030050622 -0.37294045 0.29037324 -0.47080988 0.3808142 0.72578895 2.1105554 0.21470883 0.7360044 -5.0740123 1.4570715 2.0794148 -1.170622 -1.1369241 -6.787574 -1.6733308 -132.70726 3.0985563 39.896385 -3.0502174 -6.3030596 -9.307203 0.5265378 -7.6333337 135.51064 12.037351 -0.74925816 1.761838 1.1923693 -2.3019202 -5.8404183 -2.7227983 8.196464 -4.955838 1.6468036 1.201501 1.0912888 -3.7998908 4.382412 0.11422241 2.604986 0.69013596 -2.1008105 -1.0615306 -0.6608074 5.5734963 -2.0759969 1.052841 2.57331 3.846934 1.8781905 -1.3822014 -0.33163014 0.93642795 -0.17612934 -1.5828996 3.1239378 -0.10489303 1.4757719 0.9152152 -2.6461775 -1.2541982 -2.8911169 3.0102723 -4.7677073 -0.74349916 0.823612 0.11397509 0.551276 0.8454602 -0.7801589 -0.6115488 -0.02970181 1.3432492 0.6324553 -2.4388528 -2.3501675 -2.1101446 -0.083517306 -2.8223088 -0.005319797 2.07424 -0.16837108 -0.034734655 -2.7314672 3.5083468 -0.45716798 -0.9671099 -0.0034793976 3.539732 3.3297813 -3.250378 3.3272626 1.8129976 3.0406363 -3.5287323 2.9983332 -3.9953053 -3.2798042 2.946616 2.725229 -3.7420115 4.084407 -3.9286003 -3.981155 -0.49754632 0.06889747 0.712793 0.08413247 0.23730078 0.61035615 -1.0452521 1.1886027 0.33238873 -0.5705711 0.08733274 0.6148081 1.3009518 -0.08307661 0.4100208 -0.058970023 0.7232387 0.5923612 0.28467762 -0.47306636 0.09314391 0.11879046 3.4722137 -0.943384 -1.0091307 1.6130288 -0.024686994 -0.6718356 2.819735 0.5721452 -1.8826894 2.76656 4.1659555 1.5258229 -2.2531264 0.03824836 -0.028254637 -0.41262865 -0.3620171 1.6803583 2.8834352 -4.1359463 12.435475 -5.526876 2.0830984 1.9336442 -2.3867202 -1.5439415 -0.5561904 2.0641649 0.57983273 0.957292 3.0302193 2.5309026 -3.4434037 0.9621317 2.7559671 -1.836138 0.17065823 1.3448267 2.329718 -0.9548046 1.5669187 -0.39462337 2.178352 0.91697407 0.5676015 -2.543467 2.0802646 1.607512 -0.16080569 -0.36381465 -0.3450505 -1.4095825 -0.38209265 0.7033116 1.1395731 -0.36612543 -0.028691754 -1.4336723 0.22682117 1.972688 2.3783655 -2.3203256 -0.9740621 -2.4499092 2.7208607 -2.2336535 1.9864421 0.5742496 2.042562 0.44915488 0.5886889 -0.33103484 0.5635626 0.18641117 0.15314925 1.4750367 -2.5574481 -1.4323903 3.4598317 -1.7060332 -0.73057914 0.4120432 0.66324663 0.12906042 -0.32956508 -0.8872214 -0.0043426305 1.3528489 -3.3854792 3.145732 -2.670267 -0.207525 -1.4808707 -1.1140811 1.9123619 2.2137332 -3.2446115 -1.6329749 2.5367217 2.417979 -0.7261693 3.1082633 2.0669265 3.8399112 3.953309 3.8096128 2.3395793 -2.4060104 -4.8626757 8.782084 0.5729515 5.3392324 0.5978381 10.98394 14.781475 -1.911706 -7.0225477 3.0711658 -0.08196697 -0.15069535 -0.29706174 1.0790257 -1.1020185 2.0507185 1.617925 -0.7480767 -0.8472035 0.819592 -2.1616735 0.7831927 0.46639693 -0.28835538 1.0315442 -1.1463674 -0.81843597 0.98874533 -0.28129432 0.31113765 -0.28824154 1.1003408 -0.08989422 0.0002186935 0.12852462 -0.3457676 0.21774645 -0.37092546 -0.879979 -1.0687518 -0.5461666 -0.27857515 0.83436924 0.12363262 -0.16538943 -0.22222498 0.745233 0.43001947 0.20001638 0.47947043 -144.48038 -66.18438 -114.7972 -38.37374 -242.57527 -147.4102 28.090065 -51.16492 70.702225 -45.124508]"}

util.LogInfof("check_point_feature: %s score %d %v %v", reqID, id, score[i], retInput[i])

*/

type dnnData struct {
	input []float32
	score float32
	req   string
	doc   string
}

type logData struct {
	Level   string
	Time    time.Time
	Message string
}

func parseLogMsg(msg string) (data dnnData, ok bool) {
	// check_point_feature: 1587091280694216153983 score 40566546 0.0038456554 [3.0879004 1.0358167]
	if !strings.Contains(msg, "check_point_feature: ") || !strings.Contains(msg, " score ") {
		return
	}
	const msg1Count int = 5
	var err error
	embIdx := strings.Index(msg, "[")
	msg1 := strings.TrimSpace(msg[:embIdx])
	data1 := strings.Split(msg1, " ")
	if len(data1) != msg1Count {
		log.Printf("msg len error %d %v", len(data1), data1)
		return
	}
	data.req = data1[1]
	data.doc = data1[3]
	score, err := strconv.ParseFloat(data1[4], 64)
	if err != nil {
		log.Printf("parse score %s error %v", data1[4], err)
	}
	data.score = float32(score)
	msg2 := msg[embIdx+1 : len(msg)-1]
	//log.Printf("msg2 %s", msg2)
	data2 := strings.Split(msg2, " ")
	input := make([]float32, len(data2))
	for i, d := range data2 {
		emb, err := strconv.ParseFloat(d, 64)
		if err != nil {
			//log.Printf("parse embedding %s error %v", d, err)
			continue
		}
		input[i] = float32(emb)
	}
	data.input = input
	//log.Printf("input %v", input)
	ok = true
	return
}

func loadDnnData(path string) (data map[string]dnnData) {
	file, err := os.Open(path)
	if err != nil {
		log.Printf("open %s error %v", path, err)
		return
	}
	data = make(map[string]dnnData)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		buf := scanner.Bytes()
		if len(buf) == 0 {
			continue
		}
		var oneLog logData
		err = json.Unmarshal(buf, &oneLog)
		if err != nil {
			log.Printf("unmarshal error %v", err)
			continue
		}
		//log.Printf("%v %v", oneLog.Level, oneLog.Time)
		msg := oneLog.Message
		d, ok := parseLogMsg(msg)
		if ok {
			data[d.req+"_"+d.doc] = d
		}
	}
	return
}
