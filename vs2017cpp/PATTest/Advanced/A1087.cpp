/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1087Func(void)
{
	return 0;
}


void A1087(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1087Func();
	cout << endl;
}

void A1087(void)
{
	A1087("data\\A1087-1.txt"); // 
}

