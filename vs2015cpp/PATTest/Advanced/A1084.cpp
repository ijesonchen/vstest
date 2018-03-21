/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1084Func(void)
{
	return 0;
}


void A1084(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1084Func();
	cout << endl;
}

void A1084(void)
{
	A1084("data\\A1084-1.txt"); // 
}

