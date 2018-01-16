/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1128Func(void)
{
	return 0;
}


void A1128(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1128Func();
	cout << endl;
}

void A1128(void)
{
	A1128("data\\A1128-1.txt"); // 
}

