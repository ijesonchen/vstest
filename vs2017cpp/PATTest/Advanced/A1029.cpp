/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1029Func(void)
{
	return 0;
}


void A1029(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1029Func();
	cout << endl;
}

void A1029(void)
{
	A1029("data\\A1029-1.txt"); // 
}

