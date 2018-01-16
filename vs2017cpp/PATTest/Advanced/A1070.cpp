/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1070Func(void)
{
	return 0;
}


void A1070(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1070Func();
	cout << endl;
}

void A1070(void)
{
	A1070("data\\A1070-1.txt"); // 
}

