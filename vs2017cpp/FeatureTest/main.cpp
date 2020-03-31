#include <iostream>
#include <cstring> 
#include "main.h"
#ifdef _WIN32
	#ifdef _DEBUG
		#include <vld.h>
	#endif // _DEBUG 
#endif // WIN32 
  
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
