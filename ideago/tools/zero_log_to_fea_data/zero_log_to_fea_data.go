package main

import (
	"fmt"
	"log"
	"os"
	"strings"

	"git.innotechx.com/mtrec/vstest/ideago/tools/dnn_pred_common"
)

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("exec [zero.log out_path]")

	zeroLogPath := "./data/zero.log"
	outPutPath := "./data/."

	if len(os.Args) == 3 {
		zeroLogPath = os.Args[1]
		outPutPath = os.Args[2]
	} else if len(os.Args) != 1 {
		log.Printf("invalid arg %v", os.Args)
		return
	}

	_, reqMap := dnn_pred_common.LoadZeroLog(zeroLogPath)

	for req, reqData := range reqMap {
		ids := reqData.ItemIds
		if len(ids) != len(reqData.ItemFea) {
			log.Printf("item fea not equal %s %d-%d", req, len(ids), len(reqData.ItemFea))
			continue
		}
		// use req id seq
		ids = reqData.ItemIds
		// multi line
		f, err := os.OpenFile(outPutPath+"/"+req+".txt", os.O_CREATE|os.O_RDWR|os.O_TRUNC, 0666)
		if err != nil {
			log.Printf("open file %s error %v", outPutPath, err)
			continue
		}
		// 1 ids: reqid id1 id2 ... (1 reqid N itemid)
		_, _ = f.WriteString(req)
		_, _ = f.WriteString(" ")
		_, _ = f.WriteString(strings.Trim(fmt.Sprint(ids), "[]"))
		_, _ = f.WriteString("\n")
		// 2 userdata:key@v|-|...
		_, _ = f.WriteString(reqData.UserFea)
		_, _ = f.WriteString("\n")
		// N* itemdata:key@v|-|... (N line)
		for _, iid := range ids {
			fea := reqData.ItemFea[iid]
			_, _ = f.WriteString(fea)
			_, _ = f.WriteString("\n")
		}
		f.Close()
	}
}
