/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1041Func(void)
{
	return 0;
}


void A1041(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1041Func();
	cout << endl;
}

void A1041(void)
{
	A1041("data\\A1041-1.txt"); // 
}

