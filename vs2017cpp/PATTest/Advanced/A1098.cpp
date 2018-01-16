/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1098Func(void)
{
	return 0;
}


void A1098(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1098Func();
	cout << endl;
}

void A1098(void)
{
	A1098("data\\A1098-1.txt"); // 
}

