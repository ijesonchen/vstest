/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1096Func(void)
{
	return 0;
}


void A1096(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1096Func();
	cout << endl;
}

void A1096(void)
{
	A1096("data\\A1096-1.txt"); // 
}

