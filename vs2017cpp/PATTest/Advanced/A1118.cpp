/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1118Func(void)
{
	return 0;
}


void A1118(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1118Func();
	cout << endl;
}

void A1118(void)
{
	A1118("data\\A1118-1.txt"); // 
}

