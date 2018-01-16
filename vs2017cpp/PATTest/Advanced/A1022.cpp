/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1022Func(void)
{
	return 0;
}


void A1022(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1022Func();
	cout << endl;
}

void A1022(void)
{
	A1022("data\\A1022-1.txt"); // 
}

