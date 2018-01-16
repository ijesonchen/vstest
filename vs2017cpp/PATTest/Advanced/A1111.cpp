/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1111Func(void)
{
	return 0;
}


void A1111(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1111Func();
	cout << endl;
}

void A1111(void)
{
	A1111("data\\A1111-1.txt"); // 
}

