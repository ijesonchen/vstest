/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1121Func(void)
{
	return 0;
}


void A1121(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1121Func();
	cout << endl;
}

void A1121(void)
{
	A1121("data\\A1121-1.txt"); // 
}

