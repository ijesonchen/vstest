/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1048Func(void)
{
	return 0;
}


void A1048(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1048Func();
	cout << endl;
}

void A1048(void)
{
	A1048("data\\A1048-1.txt"); // 
}

