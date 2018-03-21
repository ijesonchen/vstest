/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1069Func(void)
{
	return 0;
}


void A1069(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1069Func();
	cout << endl;
}

void A1069(void)
{
	A1069("data\\A1069-1.txt"); // 
}

