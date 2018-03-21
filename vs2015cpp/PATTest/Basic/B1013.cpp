/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1013Func(void)
{
	return 0;
}


void B1013(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1013Func();
	cout << endl;
}

void B1013(void)
{
	B1013("data\\B1013-1.txt"); // 
}

