/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1042Func(void)
{
	return 0;
}


void A1042(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1042Func();
	cout << endl;
}

void A1042(void)
{
	A1042("data\\A1042-1.txt"); // 
}

