/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1027Func(void)
{
	return 0;
}


void A1027(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1027Func();
	cout << endl;
}

void A1027(void)
{
	A1027("data\\A1027-1.txt"); // 
}

