/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1144Func(void)
{
	return 0;
}


void A1144(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1144Func();
	cout << endl;
}

void A1144(void)
{
	A1144("data\\A1144-1.txt"); // 
}

