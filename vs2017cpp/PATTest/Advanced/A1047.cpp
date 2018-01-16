/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1047Func(void)
{
	return 0;
}


void A1047(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1047Func();
	cout << endl;
}

void A1047(void)
{
	A1047("data\\A1047-1.txt"); // 
}

