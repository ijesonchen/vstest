package utils

// traceName_20191209-17123520_385119700.trace
// will create new file & prof. don't forget stop.

import (
	"io"
	"runtime/trace"
)

var (
	tracer = profInfo{
		name:  "trace",
		actor: &tracerS{},
	}
)

func TraceFileName() string {
	return tracer.profFileName()
}

func IsTracing() bool {
	return tracer.isRunning()
}

func StartTrace(prefix string) error {
	return tracer.start(prefix)
}

func StopTrace() error {
	return tracer.stop()
}

type tracerS struct{}

func (t *tracerS) start(w io.Writer) error {
	return trace.Start(w)
}

func (t *tracerS) stop() {
	trace.Stop()
}
