/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1036Func(void)
{
	return 0;
}


void A1036(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1036Func();
	cout << endl;
}

void A1036(void)
{
	A1036("data\\A1036-1.txt"); // 
}

