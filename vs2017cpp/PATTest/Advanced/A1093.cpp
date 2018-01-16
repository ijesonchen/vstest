/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1093Func(void)
{
	return 0;
}


void A1093(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1093Func();
	cout << endl;
}

void A1093(void)
{
	A1093("data\\A1093-1.txt"); // 
}

