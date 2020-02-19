package utils

import (
	"fmt"
	"strings"
	"testing"
)

func TestTracer(t *testing.T) {
	var err error
	tracerName := "tracename"

	if IsTracing() {
		t.Fatalf("TestTracer is Tracing before start")
	}

	err = StopTrace()
	if err != nil {
		t.Fatalf("TestTracer stop before start error %v", err)
	}

	err = StartTrace(tracerName)
	if err != nil {
		t.Fatalf("TestTracer start error %v", err)
	}
	err = StartTrace(tracerName)
	if err == nil {
		t.Fatalf("TestTracer start agagin passed")
	}
	if tracer.prefix != tracerName || !strings.HasPrefix(tracer.fileName, tracer.prefix) {
		t.Fatalf("TestTracer info error %q %q %q, %+v", tracerName, tracer.prefix, tracer.fileName, tracer)
	}
	if !IsTracing() {
		t.Fatalf("TestTracer not Tracing after start")
	}
	err = StopTrace()
	if err != nil {
		t.Fatalf("TestTracer stop error %v", err)
	}
	err = StopTrace()
	if err != nil {
		t.Fatalf("TestTracer stop again error %v", err)
	}
	if IsTracing() {
		t.Fatalf("TestTracer is Tracing after stop")
	}
	fmt.Println("TestTracer", tracer.prefix, tracer.fileName)
}
