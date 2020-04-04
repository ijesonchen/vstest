package main

/*
示例代码可以参考
   https://github.com/tensorflow/tensorflow.git
	tensorflow/go/saved_model.go:LoadSavedModel  资源申请，SetFinalizer
	tensorflow/go/session.go: (s *Session) Run   资源使用，KeepAlive
	tensorflow/go/session.go: (s *Session) Close 资源释放，并发处理 //这部分可以简化

   关键词 Go语言资源自动回收技术
   https://zhuanlan.zhihu.com/p/76504936 使用runtime.SetFinalizer优雅关闭后台goroutine
   https://mlog.club/article/90611  垃圾收集和cgo
   https://juejin.im/post/5d74783bf265da03ca11923d 深入理解Go-runtime.SetFinalizer原理剖析

runtime.SetFinalizer需要和runtime.KeepAlive配合使用，避免提前gc
否则有可能最后一次proc未结束时，对象就被gc回收。
SetFinalizer注册的函数阻塞不会导致gc阻塞
（go 1.14 释放是C函数中sleep 1秒，但是gc耗时和pace看起来正常。）

用途：可以通过gc来管理资源（如cgo打开的文件句柄，创建的内存对象等）
原理：将需要管理的资源放在某个go对象中，当该对象不可达（一般指针方式使用），可以触发SetFinalizer，从而回收资源。


期望输出：
2020/03/31 17:07:46 finalizer.go:63: data proc LEAVE 5
2020/03/31 17:07:46 finalizer.go:61: data proc ENTER 5
object ctor >>>> 6											// C加载新的对象LoadObject
2020/03/31 17:07:46 finalizer.go:51: object loaded  ===> 6  // go加载
2020/03/31 17:07:46 finalizer.go:63: data proc LEAVE 5      // 5全部处理完
object dtor <<<< 5											// C释放ReleaseObject
2020/03/31 17:07:46 finalizer.go:48: object offload <=== 5  // SetFinalizer执行结束
2020/03/31 17:07:46 finalizer.go:61: data proc ENTER 6      // 使用新的对象
2020/03/31 17:07:46 finalizer.go:63: data proc LEAVE 6

未添加KeepAlive时：
2020/03/31 17:04:52 finalizer.go:54: data proc ENTER 1
2020/03/31 17:04:52 finalizer.go:56: data proc LEAVE 1
2020/03/31 17:04:52 finalizer.go:54: data proc ENTER 1
model ctor >>>> 2
2020/03/31 17:04:52 finalizer.go:44: object loaded  ===> 2
model dtor <<<< 1											// 提前释放1
2020/03/31 17:04:52 finalizer.go:41: object offload <=== 1
2020/03/31 17:04:52 finalizer.go:56: data proc LEAVE 1      // 1未全部处理完
2020/03/31 17:04:52 finalizer.go:54: data proc ENTER 2
2020/03/31 17:04:52 finalizer.go:56: data proc LEAVE 2
*/

/*
	typedef struct ObjectInfo ObjectInfo;
    ObjectInfo* LoadObject(int x);
    void ReleaseObject(ObjectInfo* p);
*/
import "C"

import (
	"log"
	"math/rand"
	"runtime"
	"sync/atomic"
	"time"
)

type CObject struct {
	c  *C.ObjectInfo // type *main._Ctype_struct_ObjectInfo
	id int
}

type GlobalData struct {
	obj *CObject
	id  int
}

var globalData atomic.Value

func startObjLoader(ms float32) {
	go func() {
		i := 0
		for {
			cobj := &CObject{
				c:  C.LoadObject(C.int(i)),
				id: i,
			}
			runtime.SetFinalizer(cobj, func(p *CObject) {
				C.ReleaseObject(p.c)

				log.Printf("object offload <=== %d", p.id)
			})
			globalData.Store(GlobalData{obj: cobj, id: i})
			log.Printf("object loaded  ===> %d", i)
			i++
			time.Sleep(time.Millisecond * time.Duration(ms+rand.Float32()*ms))
		}
	}()
}

// 50-150 ms proc. avg 100ms
func proc(p interface{}) {
	data := p.(GlobalData)
	log.Printf("data proc ENTER %d", data.id)
	time.Sleep(time.Millisecond * time.Duration(50+rand.Float32()*100))
	log.Printf("data proc LEAVE %d", data.id)
	runtime.KeepAlive(p)
}

func startProc(ms float32) {
	go func() {
		for {
			time.Sleep(time.Millisecond * time.Duration(ms))
			proc(globalData.Load())
		}
	}()
}

func testFinalizer() {
	testCRes()
	rand.Seed(time.Now().UnixNano())

	// force gc
	go func() {
		for {
			runtime.GC()
			time.Sleep(time.Millisecond * 10)
		}
	}()

	// start
	startObjLoader(400)
	startProc(25)
	time.Sleep(time.Second * 5)
	log.Println("LEAVE testFinalizer")
}
