/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1112Func(void)
{
	return 0;
}


void A1112(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1112Func();
	cout << endl;
}

void A1112(void)
{
	A1112("data\\A1112-1.txt"); // 
}

