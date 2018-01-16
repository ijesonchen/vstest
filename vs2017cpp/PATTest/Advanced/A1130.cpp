/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1130Func(void)
{
	return 0;
}


void A1130(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1130Func();
	cout << endl;
}

void A1130(void)
{
	A1130("data\\A1130-1.txt"); // 
}

