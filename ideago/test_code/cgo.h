extern "C" {
	typedef struct ObjectInfo ObjectInfo;
    ObjectInfo* LoadObject(int x);
    void ReleaseObject(ObjectInfo* p);

    void* AllocMem(void);
    void FillMem(void*p, char n);
    void FreeMem(void*);
}