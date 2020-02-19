package utils

// profPrefix_20191209-17123520_385119700.profName
// will create new file & prof. don't forget stop.

import (
	"fmt"
	"io"
	"os"
	"sync"
	"time"
)

type profInfo struct {
	m        sync.Mutex
	running  bool
	name     string
	prefix   string
	fileName string
	f        *os.File
	actor    profer
}

type profer interface {
	start(w io.Writer) error
	stop()
}

// close file, lock first.
func (p *profInfo) close() (err error) {
	if err = p.f.Close(); err != nil {
		return fmt.Errorf("close %q file %q error %v", p.name, p.fileName, err)
	}
	p.f = nil
	p.fileName = ""
	return nil
}

func (p *profInfo) isRunning() bool {
	p.m.Lock()
	defer p.m.Unlock()
	return p.running
}

func (p *profInfo) profFileName() string {
	p.m.Lock()
	defer p.m.Unlock()
	return p.fileName
}

func (p *profInfo) start(prefix string) error {
	p.m.Lock()
	defer p.m.Unlock()
	if p.running {
		return fmt.Errorf("%s is running: %s", p.name, p.fileName)
	}
	var err error
	now := time.Now()
	p.prefix = prefix
	p.fileName = fmt.Sprintf("%s_%s_%09d.%s", p.prefix, now.Format("20060102-151405"), now.Nanosecond(), p.name)
	p.f, err = os.OpenFile(p.fileName, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0666)
	if err != nil {
		return fmt.Errorf("open %s %q error %v", p.name, p.fileName, err)
	}
	if err = p.actor.start(p.f); err != nil {
		_ = p.close()
		return fmt.Errorf("start %s %q error %v", p.name, p.fileName, err)
	}
	p.running = true
	return nil
}

func (p *profInfo) stop() error {
	p.m.Lock()
	defer p.m.Unlock()
	if !p.running {
		return nil
	}
	p.actor.stop()
	p.running = false
	return p.close()
}
