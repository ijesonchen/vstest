/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1143Func(void)
{
	return 0;
}


void A1143(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1143Func();
	cout << endl;
}

void A1143(void)
{
	A1143("data\\A1143-1.txt"); // 
}

