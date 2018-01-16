/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1017Func(void)
{
	return 0;
}


void A1017(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1017Func();
	cout << endl;
}

void A1017(void)
{
	A1017("data\\A1017-1.txt"); // 
}

