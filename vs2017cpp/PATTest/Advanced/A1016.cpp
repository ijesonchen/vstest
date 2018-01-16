/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1016Func(void)
{
	return 0;
}


void A1016(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1016Func();
	cout << endl;
}

void A1016(void)
{
	A1016("data\\A1016-1.txt"); // 
}

