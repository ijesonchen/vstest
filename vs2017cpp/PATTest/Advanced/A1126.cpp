/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1126Func(void)
{
	return 0;
}


void A1126(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1126Func();
	cout << endl;
}

void A1126(void)
{
	A1126("data\\A1126-1.txt"); // 
}

