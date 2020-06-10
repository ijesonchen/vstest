package main

import (
	"git.innotechx.com/mtrec/vstest/ideago/log"
)

func main() {
	log.Info("ENTER MAIN")
	defer log.Info("LEAVE MAIN")

	log.Info("END OF MAIN")
}
