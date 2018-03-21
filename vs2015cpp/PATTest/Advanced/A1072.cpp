/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1072Func(void)
{
	return 0;
}


void A1072(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1072Func();
	cout << endl;
}

void A1072(void)
{
	A1072("data\\A1072-1.txt"); // 
}

