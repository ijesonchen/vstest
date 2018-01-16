/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1148Func(void)
{
	return 0;
}


void A1148(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1148Func();
	cout << endl;
}

void A1148(void)
{
	A1148("data\\A1148-1.txt"); // 
}

