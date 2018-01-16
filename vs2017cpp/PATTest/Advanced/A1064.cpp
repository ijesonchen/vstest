/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1064Func(void)
{
	return 0;
}


void A1064(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1064Func();
	cout << endl;
}

void A1064(void)
{
	A1064("data\\A1064-1.txt"); // 
}

