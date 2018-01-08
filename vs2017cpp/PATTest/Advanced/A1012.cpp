/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1012Func(void)
{
	return 0;
}


void A1012(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1012Func();
	cout << endl;
}

void A1012(void)
{
	A1012("data\\A1012-1.txt"); // 
}

