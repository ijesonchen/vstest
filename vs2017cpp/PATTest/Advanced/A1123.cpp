/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1123Func(void)
{
	return 0;
}


void A1123(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1123Func();
	cout << endl;
}

void A1123(void)
{
	A1123("data\\A1123-1.txt"); // 
}

