/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1097Func(void)
{
	return 0;
}


void A1097(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1097Func();
	cout << endl;
}

void A1097(void)
{
	A1097("data\\A1097-1.txt"); // 
}

