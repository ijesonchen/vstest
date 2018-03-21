/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1146Func(void)
{
	return 0;
}


void A1146(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1146Func();
	cout << endl;
}

void A1146(void)
{
	A1146("data\\A1146-1.txt"); // 
}

