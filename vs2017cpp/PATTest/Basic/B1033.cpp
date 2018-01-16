/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1033Func(void)
{
	return 0;
}


void B1033(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1033Func();
	cout << endl;
}

void B1033(void)
{
	B1033("data\\B1033-1.txt"); // 
}

