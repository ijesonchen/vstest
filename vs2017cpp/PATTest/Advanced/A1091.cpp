/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1091Func(void)
{
	return 0;
}


void A1091(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1091Func();
	cout << endl;
}

void A1091(void)
{
	A1091("data\\A1091-1.txt"); // 
}

