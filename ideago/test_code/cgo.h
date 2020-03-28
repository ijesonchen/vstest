extern "C" {
    int LoadModel2(const char* fnHash, const char* fnEmbed);
    int ProcData(void* pvinInt, void* pvoutFloat, int nLen);
}