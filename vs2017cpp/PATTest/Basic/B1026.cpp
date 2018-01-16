/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1026Func(void)
{
	return 0;
}


void B1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1026Func();
	cout << endl;
}

void B1026(void)
{
	B1026("data\\B1026-1.txt"); // 
}

