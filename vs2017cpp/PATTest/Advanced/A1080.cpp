/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1080Func(void)
{
	return 0;
}


void A1080(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1080Func();
	cout << endl;
}

void A1080(void)
{
	A1080("data\\A1080-1.txt"); // 
}

