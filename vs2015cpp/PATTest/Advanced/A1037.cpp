/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1037Func(void)
{
	return 0;
}


void A1037(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1037Func();
	cout << endl;
}

void A1037(void)
{
	A1037("data\\A1037-1.txt"); // 
}

