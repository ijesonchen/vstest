/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1004Func(void)
{
	return 0;
}


void B1004(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1004Func();
	cout << endl;
}

void B1004(void)
{
	B1004("data\\B1004-1.txt"); // 
}

