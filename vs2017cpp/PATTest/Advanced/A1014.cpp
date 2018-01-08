/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1014Func(void)
{
	return 0;
}


void A1014(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1014Func();
	cout << endl;
}

void A1014(void)
{
	A1014("data\\A1014-1.txt"); // 
}

