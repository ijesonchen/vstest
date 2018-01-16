/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1040Func(void)
{
	return 0;
}


void B1040(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1040Func();
	cout << endl;
}

void B1040(void)
{
	B1040("data\\B1040-1.txt"); // 
}

