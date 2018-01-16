/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1105Func(void)
{
	return 0;
}


void A1105(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1105Func();
	cout << endl;
}

void A1105(void)
{
	A1105("data\\A1105-1.txt"); // 
}

