/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1114Func(void)
{
	return 0;
}


void A1114(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1114Func();
	cout << endl;
}

void A1114(void)
{
	A1114("data\\A1114-1.txt"); // 
}

