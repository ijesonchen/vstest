/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1086Func(void)
{
	return 0;
}


void A1086(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1086Func();
	cout << endl;
}

void A1086(void)
{
	A1086("data\\A1086-1.txt"); // 
}

