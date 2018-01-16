/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1075Func(void)
{
	return 0;
}


void A1075(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1075Func();
	cout << endl;
}

void A1075(void)
{
	A1075("data\\A1075-1.txt"); // 
}

