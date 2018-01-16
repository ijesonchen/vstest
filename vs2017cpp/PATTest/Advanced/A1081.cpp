/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1081Func(void)
{
	return 0;
}


void A1081(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1081Func();
	cout << endl;
}

void A1081(void)
{
	A1081("data\\A1081-1.txt"); // 
}

