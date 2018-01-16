/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1119Func(void)
{
	return 0;
}


void A1119(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1119Func();
	cout << endl;
}

void A1119(void)
{
	A1119("data\\A1119-1.txt"); // 
}

