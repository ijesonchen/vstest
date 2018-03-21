/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1090Func(void)
{
	return 0;
}


void A1090(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1090Func();
	cout << endl;
}

void A1090(void)
{
	A1090("data\\A1090-1.txt"); // 
}

