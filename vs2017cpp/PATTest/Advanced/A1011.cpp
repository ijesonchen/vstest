/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1011Func(void)
{
	return 0;
}


void A1011(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1011Func();
	cout << endl;
}

void A1011(void)
{
	A1011("data\\A1011-1.txt"); // 
}

