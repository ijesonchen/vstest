/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1131Func(void)
{
	return 0;
}


void A1131(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1131Func();
	cout << endl;
}

void A1131(void)
{
	A1131("data\\A1131-1.txt"); // 
}

