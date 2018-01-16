/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1065Func(void)
{
	return 0;
}


void A1065(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1065Func();
	cout << endl;
}

void A1065(void)
{
	A1065("data\\A1065-1.txt"); // 
}

