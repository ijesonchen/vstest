/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1083Func(void)
{
	return 0;
}


void A1083(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1083Func();
	cout << endl;
}

void A1083(void)
{
	A1083("data\\A1083-1.txt"); // 
}

