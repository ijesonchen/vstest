/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1116Func(void)
{
	return 0;
}


void A1116(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1116Func();
	cout << endl;
}

void A1116(void)
{
	A1116("data\\A1116-1.txt"); // 
}

