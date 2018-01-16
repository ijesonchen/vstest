/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1066Func(void)
{
	return 0;
}


void A1066(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1066Func();
	cout << endl;
}

void A1066(void)
{
	A1066("data\\A1066-1.txt"); // 
}

