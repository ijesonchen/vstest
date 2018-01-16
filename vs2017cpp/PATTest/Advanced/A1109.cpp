/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1109Func(void)
{
	return 0;
}


void A1109(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1109Func();
	cout << endl;
}

void A1109(void)
{
	A1109("data\\A1109-1.txt"); // 
}

