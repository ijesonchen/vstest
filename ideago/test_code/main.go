package main

import (
	"log"

	"git.innotechx.com/mtrec/vstest/ideago/utils"
)

func init() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
}

func main() {
	log.Println("ENTER MAIN")
	defer log.Println("LEAVE MAIN")

	addrs, err := utils.GetIpAddr()
	log.Printf("%v %+v", err, addrs)
}
