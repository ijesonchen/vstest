/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1079Func(void)
{
	return 0;
}


void A1079(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1079Func();
	cout << endl;
}

void A1079(void)
{
	A1079("data\\A1079-1.txt"); // 
}

