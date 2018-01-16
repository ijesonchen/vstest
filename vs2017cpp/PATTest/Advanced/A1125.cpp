/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1125Func(void)
{
	return 0;
}


void A1125(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1125Func();
	cout << endl;
}

void A1125(void)
{
	A1125("data\\A1125-1.txt"); // 
}

