extern "C" {
    int LoadModel(int n);
    int ProcData(void* pvinInt, void* pvoutFloat, size_t nLen);
}