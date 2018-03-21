/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1056Func(void)
{
	return 0;
}


void A1056(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1056Func();
	cout << endl;
}

void A1056(void)
{
	A1056("data\\A1056-1.txt"); // 
}

