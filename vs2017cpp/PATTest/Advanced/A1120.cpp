/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1120Func(void)
{
	return 0;
}


void A1120(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1120Func();
	cout << endl;
}

void A1120(void)
{
	A1120("data\\A1120-1.txt"); // 
}

