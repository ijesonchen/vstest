#include <iostream>
#include <cstring> 
#include <sstream>
#include <vector>
#include "main.h"
#ifdef _WIN32
	#ifdef _DEBUG
		#include <vld.h>
	#endif // _DEBUG 
#endif // WIN32 

void debug_print(int& v) {
	printf("%d, ", v);
}

using namespace std;

struct TTT {
	int x = 0;
	TTT() { cout << "ctor TTT" << endl; }
	TTT(TTT&) { cout << "ctor TTT copy" << endl; }
	TTT& operator=(const TTT&) { cout << "= TTT" << endl; return *this; }
	~TTT() { cout << "dtor TTT" << endl; }
};
 

vector<int> getProbs(int nlist) {
    vector<int> v;
    for (int i = 1; i < nlist && i < 5; i++) {
        v.push_back(i);
    }
    for (int i = 5; i < nlist && i < 20; i += 5) {
        v.push_back(i);
    }
    for (int i = 20; i < nlist&&i<100; i += 10) {
        v.push_back(i);
    }
    for (int i = 100; i < nlist; i += 50) {
        v.push_back(i);
    }
    return std::move(v);
}

int main(void) { 
    auto v = getProbs(3);
    v = getProbs(30);
    v = getProbs(300);
 	auto p = new char; // for memory leak detect
 	cout << "enter to continue" << endl;
	string s;
//	getline(cin, s);
	getchar();
    return 0;
}
