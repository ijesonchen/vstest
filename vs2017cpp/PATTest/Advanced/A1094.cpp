/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1094Func(void)
{
	return 0;
}


void A1094(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1094Func();
	cout << endl;
}

void A1094(void)
{
	A1094("data\\A1094-1.txt"); // 
}

