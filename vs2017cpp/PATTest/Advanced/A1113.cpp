/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1113Func(void)
{
	return 0;
}


void A1113(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1113Func();
	cout << endl;
}

void A1113(void)
{
	A1113("data\\A1113-1.txt"); // 
}

