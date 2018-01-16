/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1061Func(void)
{
	return 0;
}


void A1061(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1061Func();
	cout << endl;
}

void A1061(void)
{
	A1061("data\\A1061-1.txt"); // 
}

