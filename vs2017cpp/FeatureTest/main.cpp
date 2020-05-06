#include <iostream>
#include <cstring> 
#include <sstream>
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
 


int main(void) {  
	ThreadTest();
 	auto p = new char; // for memory leak detect
 	cout << "enter to continue" << endl;
	string s;
//	getline(cin, s);
	getchar();
    return 0;
}
