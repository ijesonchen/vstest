#include <atomic>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <filesystem>

void FstreamTest(void);
 
using namespace std;
 
int fstreamRead(const char* fnHash) {
    if (fnHash == nullptr) {
        puts("invalid parameter.");
        return -3;
    }
    if (!filesystem::exists(fnHash)) {
        printf("file [%s] not exists.\n", fnHash);
        return -4;
    }
    auto nFileLen = filesystem::file_size(fnHash);
    printf("** %s length %zd\n", fnHash, nFileLen);

    ifstream fHash(fnHash, ios::binary | ios::in);
    if (!fHash.is_open()) {
        printf("open file %s error", fnHash);
        return -1;
    }
    auto buf = new unsigned char[1000];
    int nLen = 10;
    size_t nTotal = 0, nRead = 0;
    while (fHash.read((char*)buf, nLen)) {
        nRead = fHash.gcount();
        nTotal += nRead;
        buf[nRead] = 0;
        printf("data %lld [%s]\n", nRead, buf);
    }

    nRead = fHash.gcount();
    if (nRead > 0) {
        nTotal += nRead;
        buf[nRead] = 0;
        printf("data %lld [%s]\n", nRead, buf);
    }

    if (!fHash.eof()) {
        printf("**read error\n");
    }
    printf("**read total %zd\n", nTotal);

    return 0;
} 

void FstreamTest() {
    auto n = fstreamRead("common.cpp");
    printf("return %d\n", n);
}