/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1101Func(void)
{
	return 0;
}


void A1101(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1101Func();
	cout << endl;
}

void A1101(void)
{
	A1101("data\\A1101-1.txt"); // 
}

