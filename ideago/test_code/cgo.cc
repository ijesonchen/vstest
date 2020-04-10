#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <unistd.h>
#include <iostream>
#include "cgo.h"

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