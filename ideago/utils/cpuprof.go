package utils

// cpuProfName_20191209-17123520_385119700.cpuProf
// will create new file & prof. don't forget stop.

import (
	"io"
	"runtime/pprof"
)

var (
	cpuProfer = profInfo{
		name:  "cpuProf",
		actor: &cpuProfS{},
	}
)

func CpuProfFileName() string {
	return cpuProfer.profFileName()
}

func IsCpuProfiling() bool {
	return cpuProfer.isRunning()
}

func StartCpuProf(prefix string) error {
	return cpuProfer.start(prefix)
}

func StopCpuProf() error {
	return cpuProfer.stop()
}

type cpuProfS struct{}

func (t *cpuProfS) start(w io.Writer) error {
	return pprof.StartCPUProfile(w)
}

func (t *cpuProfS) stop() {
	pprof.StopCPUProfile()
}
