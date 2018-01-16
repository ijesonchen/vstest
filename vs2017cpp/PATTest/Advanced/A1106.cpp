/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1106Func(void)
{
	return 0;
}


void A1106(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1106Func();
	cout << endl;
}

void A1106(void)
{
	A1106("data\\A1106-1.txt"); // 
}

