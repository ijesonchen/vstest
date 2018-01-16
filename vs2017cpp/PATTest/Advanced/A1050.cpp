/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1050Func(void)
{
	return 0;
}


void A1050(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1050Func();
	cout << endl;
}

void A1050(void)
{
	A1050("data\\A1050-1.txt"); // 
}

