/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1140Func(void)
{
	return 0;
}


void A1140(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1140Func();
	cout << endl;
}

void A1140(void)
{
	A1140("data\\A1140-1.txt"); // 
}

