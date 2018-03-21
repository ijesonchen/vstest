/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1051Func(void)
{
	return 0;
}


void A1051(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1051Func();
	cout << endl;
}

void A1051(void)
{
	A1051("data\\A1051-1.txt"); // 
}

