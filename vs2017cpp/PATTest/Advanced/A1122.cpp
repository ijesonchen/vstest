/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1122Func(void)
{
	return 0;
}


void A1122(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1122Func();
	cout << endl;
}

void A1122(void)
{
	A1122("data\\A1122-1.txt"); // 
}

