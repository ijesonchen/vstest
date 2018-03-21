/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1073Func(void)
{
	return 0;
}


void A1073(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1073Func();
	cout << endl;
}

void A1073(void)
{
	A1073("data\\A1073-1.txt"); // 
}

