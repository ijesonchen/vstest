/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1057Func(void)
{
	return 0;
}


void A1057(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1057Func();
	cout << endl;
}

void A1057(void)
{
	A1057("data\\A1057-1.txt"); // 
}

