/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1054Func(void)
{
	return 0;
}


void A1054(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1054Func();
	cout << endl;
}

void A1054(void)
{
	A1054("data\\A1054-1.txt"); // 
}

