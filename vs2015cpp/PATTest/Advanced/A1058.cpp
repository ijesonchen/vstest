/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1058Func(void)
{
	return 0;
}


void A1058(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1058Func();
	cout << endl;
}

void A1058(void)
{
	A1058("data\\A1058-1.txt"); // 
}

