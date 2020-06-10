package main

import (
	"errors"
	"github.com/colinmarc/hdfs"
	"log"
	"os"
	"strings"
)

func main() {
	// hdfs://pub1/innodata/dw/rec_mengtui.db/hqd_bert_mt/g_embeds.csv
	clientOptions := hdfs.ClientOptions{
		Addresses: []string{"xxxx1:8020", "xxxx2:8020"},
		User:      "hadoop",
	}
	client, err := hdfs.NewClient(clientOptions)

	if err != nil {
		log.Printf("new error %v", err)
		return
	}

	info, err := client.Stat("/innodata/dw/rec_mengtui.db/hqd_bert_mt/g_embeds.csv")
	if err != nil {
		log.Printf("stat error %v", err)
		return
	}

	// type WalkFunc func(path string, info os.FileInfo, err error) error
	//wf := func(path string, info os.FileInfo, err0 error) (err error){
	//	log.Printf("walk %s %s %d %t", path, info.Name(), info.Size(), info.IsDir())
	//	return nil
	//}

	//err = client.Walk("/innodata/dw/rec_mengtui.db/", wf)
	//log.Printf("err %v", err)

	err = DownDir(client, "/innodata/dw/rec_mengtui.db/", "./down")
	log.Printf("down dir err %v", err)

	log.Printf("name %v size %v mod %v", info.Name(), info.Size(), info.ModTime())
}

func DownDir(client *hdfs.Client, srcPath, dstPath string) (err error) {
	if dstPath[len(dstPath)-1] != '/' {
		dstPath = dstPath + "/"
	}
	log.Printf("src [%s] dst [%s]", srcPath, dstPath)
	d := true
	f := true
	nd := 0
	nf := 0
	walkFunc := func(path string, info os.FileInfo, err0 error) (err error) {
		log.Printf("==>path %v", path)
		local := dstPath + strings.TrimPrefix(path, srcPath)
		log.Printf("walk %t %s", info.IsDir(), local)
		if d && info.IsDir() {
			nd++
			if nd > 10 {
				d = false
			}
			return os.MkdirAll(local, 0666)
		}
		if f && !info.IsDir() {
			nf++
			if nf > 10 {
				f = false
			}
			n := strings.LastIndex(local, "/")
			if n > 0 {
				localDir := local[:n]
				log.Printf("mkdir local %s %v", localDir, os.MkdirAll(localDir, 0666))
			}
			return client.CopyToLocal(path, local)
		}
		if !d && !f {
			return errors.New("down")
		}
		return nil
	}

	return client.Walk(srcPath, walkFunc)
}
