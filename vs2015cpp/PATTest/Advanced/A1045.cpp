/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1045Func(void)
{
	return 0;
}


void A1045(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1045Func();
	cout << endl;
}

void A1045(void)
{
	A1045("data\\A1045-1.txt"); // 
}

