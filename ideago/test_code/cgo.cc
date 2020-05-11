#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string.h>
#include "cgo.h"

using namespace std;

void testf(void){
  std::cout << "test"<<std::endl;
}

struct ObjectInfo{

    ObjectInfo(int a){
        x=a;
        printf("object ctor >>>> %d\n",x);
    }
    ~ObjectInfo(){printf("object dtor <<<< %d\n",x);};

    int x;
};

ObjectInfo* LoadObject(int x){
    return  new ObjectInfo(x);
}

void ReleaseObject(ObjectInfo* p){
    printf("enter ReleaseObject %d\n", p->x);
    sleep(1);
    printf("awake ReleaseObject %d\n", p->x);
    delete  p;
    printf("leave ReleaseObject %d\n", p->x);
}

struct AllocHolder{
    int siz;
    char* p;
    vector<int> v;

    AllocHolder(){
    siz = 0;
    p = 0;
    }

    ~AllocHolder(){
    delete[] p;
    }
};

void* AllocMem(void){
    int siz = 100*1024*1024;

    struct AllocHolder* p = new AllocHolder();
    p->siz = siz;
    p->p = new char[siz];
    memset(p->p, 0, siz);
    p->v.resize(siz);
    return p;
}

void FillMem(void*p, char n){
    struct AllocHolder*p1 = (AllocHolder*)p;
    int i = 0;
    for (i = 0;i<p1->siz;i++){
        p1->p[i]=n;
        p1->v[i]=n;
    }
}

void FreeMemThread(AllocHolder* p){
    this_thread::sleep_for(chrono::seconds(1));
    delete p;
}

void FreeMem(void* p){
    thread t(FreeMemThread, (AllocHolder*)p);
    t.detach();
}