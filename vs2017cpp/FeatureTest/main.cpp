#include <iostream>
#include <cstring> 
//#include "main.h"
#ifdef _WIN32
	#ifdef _DEBUG
		#include <vld.h>
	#endif // _DEBUG 
#endif // WIN32 
 

void BlankTest();
using namespace std;
int main(void) { 
	cout << "compiled on " << __DATE__ << " " << __TIME__ << endl;
	//BlankTest();
	auto p = new char; 
 	cout << "enter to continue" << endl;
	string s;
//	getline(cin, s);
	getchar();
    return 0;
}
