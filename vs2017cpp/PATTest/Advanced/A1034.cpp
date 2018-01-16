/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1034Func(void)
{
	return 0;
}


void A1034(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1034Func();
	cout << endl;
}

void A1034(void)
{
	A1034("data\\A1034-1.txt"); // 
}

