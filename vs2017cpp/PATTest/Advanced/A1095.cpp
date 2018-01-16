/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1095Func(void)
{
	return 0;
}


void A1095(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1095Func();
	cout << endl;
}

void A1095(void)
{
	A1095("data\\A1095-1.txt"); // 
}

