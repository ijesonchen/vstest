/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1060Func(void)
{
	return 0;
}


void A1060(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1060Func();
	cout << endl;
}

void A1060(void)
{
	A1060("data\\A1060-1.txt"); // 
}

