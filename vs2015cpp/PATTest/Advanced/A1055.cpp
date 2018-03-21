/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1055Func(void)
{
	return 0;
}


void A1055(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1055Func();
	cout << endl;
}

void A1055(void)
{
	A1055("data\\A1055-1.txt"); // 
}

