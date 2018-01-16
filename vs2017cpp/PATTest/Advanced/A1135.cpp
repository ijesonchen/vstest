/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1135Func(void)
{
	return 0;
}


void A1135(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1135Func();
	cout << endl;
}

void A1135(void)
{
	A1135("data\\A1135-1.txt"); // 
}

