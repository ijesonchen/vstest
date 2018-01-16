/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1088Func(void)
{
	return 0;
}


void A1088(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1088Func();
	cout << endl;
}

void A1088(void)
{
	A1088("data\\A1088-1.txt"); // 
}

