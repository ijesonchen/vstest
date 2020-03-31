#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "cgo.h"

struct ObjectInfo{

    ObjectInfo(int a){
        x=a;
        printf("object ctor >>>> %d\n",x);
    }
    ~ObjectInfo(){printf("object dtor <<<< %d\n",x);};
private:
    int x;
};

ObjectInfo* LoadObject(int x){
    return  new ObjectInfo(x);
}

void ReleaseObject(ObjectInfo* p){
    delete  p;
}