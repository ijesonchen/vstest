/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1110Func(void)
{
	return 0;
}


void A1110(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1110Func();
	cout << endl;
}

void A1110(void)
{
	A1110("data\\A1110-1.txt"); // 
}

