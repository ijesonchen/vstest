/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1149Func(void)
{
	return 0;
}


void A1149(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1149Func();
	cout << endl;
}

void A1149(void)
{
	A1149("data\\A1149-1.txt"); // 
}

