/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1063Func(void)
{
	return 0;
}


void A1063(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1063Func();
	cout << endl;
}

void A1063(void)
{
	A1063("data\\A1063-1.txt"); // 
}

