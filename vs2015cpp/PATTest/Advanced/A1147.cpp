/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1147Func(void)
{
	return 0;
}


void A1147(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1147Func();
	cout << endl;
}

void A1147(void)
{
	A1147("data\\A1147-1.txt"); // 
}

