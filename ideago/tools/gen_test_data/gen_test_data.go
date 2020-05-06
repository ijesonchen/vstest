package main

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
	"strings"

	"git.innotechx.com/mtrec/vstest/ideago/tools/dnn_pred_common"
)

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("exec [con.log zero.log out_path]")

	conLogPath := "./data/console.log"
	zeroLogPath := "./data/zero.log"
	outPutPath := "./data/."

	if len(os.Args) == 4 {
		conLogPath = os.Args[1]
		zeroLogPath = os.Args[2]
		outPutPath = os.Args[3]
	} else if len(os.Args) != 1 {
		log.Printf("invalid arg %v", os.Args)
		return
	}

	hashMap, idMap := dnn_pred_common.LoadConsoleLog(conLogPath)
	reqMap := dnn_pred_common.AppendZeroLog(zeroLogPath, hashMap)

	for req, reqData := range reqMap {
		hashData, ok := hashMap[req]
		if !ok {
			log.Printf("hashMap not found %s", req)
			continue
		}
		ids := idMap[req]
		if len(ids) != len(reqData.ItemIds) {
			log.Printf("ids not equal %s %d-%d: %v %v", req, len(ids), len(reqData.ItemIds), ids, reqData.ItemIds)
			continue
		}
		nItem := len(ids)
		if nItem != len(reqData.ItemFea) {
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
		// N* json: id len r_id iid score (N line)
		for _, iid := range ids {
			cp, ok := hashData[iid]
			if !ok {
				log.Printf("%s %d check point not found", req, iid)
				_, _ = f.WriteString("{}\n")
				continue
			}
			cpv1 := dnn_pred_common.CheckPointV1{
				Id:    cp.Id,
				Len:   cp.Len,
				Rid:   cp.Rid,
				Iid:   cp.Iid,
				Score: cp.Score,
			}
			b, err := json.Marshal(&cpv1)
			if err != nil {
				log.Printf("%s %d Marshal check point error %v", req, iid, err)
				b = []byte("{}")
			}
			_, _ = f.Write(b)
			_, _ = f.WriteString("\n")
		}
		// N* embedding: xx,xx (N line, emb_size each)
		for _, iid := range ids {
			cp, ok := hashData[iid]
			if !ok {
				log.Printf("%s %d check point not found", req, iid)
				_, _ = f.WriteString("\n")
				continue
			}
			_, _ = f.WriteString(strings.Trim(fmt.Sprint(cp.Embed), "[]"))
			_, _ = f.WriteString("\n")
		}
		f.Close()
	}
}
