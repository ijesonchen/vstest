/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1071Func(void)
{
	return 0;
}


void A1071(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1071Func();
	cout << endl;
}

void A1071(void)
{
	A1071("data\\A1071-1.txt"); // 
}

