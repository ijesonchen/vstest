/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1068Func(void)
{
	return 0;
}


void A1068(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1068Func();
	cout << endl;
}

void A1068(void)
{
	A1068("data\\A1068-1.txt"); // 
}

