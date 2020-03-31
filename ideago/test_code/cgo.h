extern "C" {
	typedef struct ObjectInfo ObjectInfo;
    ObjectInfo* LoadObject(int x);
    void ReleaseObject(ObjectInfo* p);
}