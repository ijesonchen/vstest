/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1127Func(void)
{
	return 0;
}


void A1127(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1127Func();
	cout << endl;
}

void A1127(void)
{
	A1127("data\\A1127-1.txt"); // 
}

