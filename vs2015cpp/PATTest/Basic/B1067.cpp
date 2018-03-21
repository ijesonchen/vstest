/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1067Func(void)
{
	return 0;
}


void B1067(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1067Func();
	cout << endl;
}

void B1067(void)
{
	B1067("data\\B1067-1.txt"); // 
}

