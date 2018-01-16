/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1089Func(void)
{
	return 0;
}


void A1089(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1089Func();
	cout << endl;
}

void A1089(void)
{
	A1089("data\\A1089-1.txt"); // 
}

