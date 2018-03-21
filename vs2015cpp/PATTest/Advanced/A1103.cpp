/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1103Func(void)
{
	return 0;
}


void A1103(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1103Func();
	cout << endl;
}

void A1103(void)
{
	A1103("data\\A1103-1.txt"); // 
}

