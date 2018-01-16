/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1043Func(void)
{
	return 0;
}


void A1043(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1043Func();
	cout << endl;
}

void A1043(void)
{
	A1043("data\\A1043-1.txt"); // 
}

