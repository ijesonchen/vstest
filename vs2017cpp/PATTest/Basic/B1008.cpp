/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1008Func(void)
{
	return 0;
}


void B1008(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1008Func();
	cout << endl;
}

void B1008(void)
{
	B1008("data\\B1008-1.txt"); // 
}

