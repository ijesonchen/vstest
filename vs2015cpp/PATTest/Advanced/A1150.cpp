/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1150Func(void)
{
	return 0;
}


void A1150(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1150Func();
	cout << endl;
}

void A1150(void)
{
	A1150("data\\A1150-1.txt"); // 
}

