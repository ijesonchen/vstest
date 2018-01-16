/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1082Func(void)
{
	return 0;
}


void A1082(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1082Func();
	cout << endl;
}

void A1082(void)
{
	A1082("data\\A1082-1.txt"); // 
}

