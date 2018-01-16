/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1104Func(void)
{
	return 0;
}


void A1104(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1104Func();
	cout << endl;
}

void A1104(void)
{
	A1104("data\\A1104-1.txt"); // 
}

