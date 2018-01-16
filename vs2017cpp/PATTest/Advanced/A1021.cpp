/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1021Func(void)
{
	return 0;
}


void A1021(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1021Func();
	cout << endl;
}

void A1021(void)
{
	A1021("data\\A1021-1.txt"); // 
}

