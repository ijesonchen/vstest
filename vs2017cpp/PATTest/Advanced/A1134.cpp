/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1134Func(void)
{
	return 0;
}


void A1134(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1134Func();
	cout << endl;
}

void A1134(void)
{
	A1134("data\\A1134-1.txt"); // 
}

