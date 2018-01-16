/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1052Func(void)
{
	return 0;
}


void A1052(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1052Func();
	cout << endl;
}

void A1052(void)
{
	A1052("data\\A1052-1.txt"); // 
}

