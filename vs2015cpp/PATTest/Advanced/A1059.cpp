/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1059Func(void)
{
	return 0;
}


void A1059(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1059Func();
	cout << endl;
}

void A1059(void)
{
	A1059("data\\A1059-1.txt"); // 
}

