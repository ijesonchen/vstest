/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1039Func(void)
{
	return 0;
}


void A1039(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1039Func();
	cout << endl;
}

void A1039(void)
{
	A1039("data\\A1039-1.txt"); // 
}

