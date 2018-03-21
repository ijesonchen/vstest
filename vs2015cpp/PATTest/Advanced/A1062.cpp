/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1062Func(void)
{
	return 0;
}


void A1062(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1062Func();
	cout << endl;
}

void A1062(void)
{
	A1062("data\\A1062-1.txt"); // 
}

