/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1076Func(void)
{
	return 0;
}


void A1076(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1076Func();
	cout << endl;
}

void A1076(void)
{
	A1076("data\\A1076-1.txt"); // 
}

