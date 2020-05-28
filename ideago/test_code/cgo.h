extern "C" {
	typedef struct ObjectInfo ObjectInfo;
    ObjectInfo* LoadObject(int x);
    void ReleaseObject(ObjectInfo* p);

    char* AllocChar(int n);
    void  FreeChar(char* p);

    void* AllocMem(void);
    void FillMem(void*p, char n);
    void FreeMem(void*);
}