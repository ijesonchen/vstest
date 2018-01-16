/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1102Func(void)
{
	return 0;
}


void A1102(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1102Func();
	cout << endl;
}

void A1102(void)
{
	A1102("data\\A1102-1.txt"); // 
}

