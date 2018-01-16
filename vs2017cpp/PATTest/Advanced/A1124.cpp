/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1124Func(void)
{
	return 0;
}


void A1124(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1124Func();
	cout << endl;
}

void A1124(void)
{
	A1124("data\\A1124-1.txt"); // 
}

