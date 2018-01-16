/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1015Func(void)
{
	return 0;
}


void A1015(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1015Func();
	cout << endl;
}

void A1015(void)
{
	A1015("data\\A1015-1.txt"); // 
}

