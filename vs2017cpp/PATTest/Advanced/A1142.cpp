/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1142Func(void)
{
	return 0;
}


void A1142(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1142Func();
	cout << endl;
}

void A1142(void)
{
	A1142("data\\A1142-1.txt"); // 
}

