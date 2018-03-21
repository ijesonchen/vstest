/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1129Func(void)
{
	return 0;
}


void A1129(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1129Func();
	cout << endl;
}

void A1129(void)
{
	A1129("data\\A1129-1.txt"); // 
}

