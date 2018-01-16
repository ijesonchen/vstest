/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1020Func(void)
{
	return 0;
}


void A1020(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1020Func();
	cout << endl;
}

void A1020(void)
{
	A1020("data\\A1020-1.txt"); // 
}

