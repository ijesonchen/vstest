/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1083Func(void)
{
	return 0;
}


void B1083(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1083Func();
	cout << endl;
}

void B1083(void)
{
	B1083("data\\B1083-1.txt"); // 
}

