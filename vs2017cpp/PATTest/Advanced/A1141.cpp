/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1141Func(void)
{
	return 0;
}


void A1141(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1141Func();
	cout << endl;
}

void A1141(void)
{
	A1141("data\\A1141-1.txt"); // 
}

