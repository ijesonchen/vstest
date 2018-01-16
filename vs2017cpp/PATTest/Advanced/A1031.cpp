/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1031Func(void)
{
	return 0;
}


void A1031(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1031Func();
	cout << endl;
}

void A1031(void)
{
	A1031("data\\A1031-1.txt"); // 
}

