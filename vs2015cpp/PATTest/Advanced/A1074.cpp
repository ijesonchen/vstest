/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1074Func(void)
{
	return 0;
}


void A1074(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1074Func();
	cout << endl;
}

void A1074(void)
{
	A1074("data\\A1074-1.txt"); // 
}

