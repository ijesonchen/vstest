/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1035Func(void)
{
	return 0;
}


void A1035(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1035Func();
	cout << endl;
}

void A1035(void)
{
	A1035("data\\A1035-1.txt"); // 
}

