/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1023Func(void)
{
	return 0;
}


void A1023(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1023Func();
	cout << endl;
}

void A1023(void)
{
	A1023("data\\A1023-1.txt"); // 
}

