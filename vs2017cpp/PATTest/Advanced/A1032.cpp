/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1032Func(void)
{
	return 0;
}


void A1032(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1032Func();
	cout << endl;
}

void A1032(void)
{
	A1032("data\\A1032-1.txt"); // 
}

