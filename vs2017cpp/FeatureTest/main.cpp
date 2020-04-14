#include <iostream>
#include <cstring> 
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
int main(void) {
	StringTest();
 	auto p = new char; // for memory leak detect
 	cout << "enter to continue" << endl;
	string s;
//	getline(cin, s);
	getchar();
    return 0;
}
