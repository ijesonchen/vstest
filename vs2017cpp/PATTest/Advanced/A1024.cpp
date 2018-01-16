/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1024Func(void)
{
	return 0;
}


void A1024(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1024Func();
	cout << endl;
}

void A1024(void)
{
	A1024("data\\A1024-1.txt"); // 
}

