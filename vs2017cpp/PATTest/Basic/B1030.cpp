/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1030Func(void)
{
	return 0;
}


void B1030(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1030Func();
	cout << endl;
}

void B1030(void)
{
	B1030("data\\B1030-1.txt"); // 
}

