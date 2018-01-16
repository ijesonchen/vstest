/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1100Func(void)
{
	return 0;
}


void A1100(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1100Func();
	cout << endl;
}

void A1100(void)
{
	A1100("data\\A1100-1.txt"); // 
}

