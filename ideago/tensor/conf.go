package main

import (
	"gopkg.in/yaml.v2"
	"io/ioutil"
	"log"
)

type Conf struct {
	DataPath   string `yaml:"DataPath"`
	TensorFlow struct {
		ModPath string `yaml:"ModPath"`
		Output  string `yaml:"Output"`
	} `yaml:"TensorFlow"`
}

func LoadConf() (conf *Conf) {
	confPath := "./conf.yaml"
	buf, err := ioutil.ReadFile(confPath)
	if err != nil {
		log.Printf("read conf %s error %v", confPath, err)
		return
	}
	conf = &Conf{}
	err = yaml.Unmarshal(buf, conf)
	if err != nil {
		log.Printf("parse conf error %v", err)
		return nil
	}
	return
}
