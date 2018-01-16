/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1089Func(void)
{
	return 0;
}


void B1089(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1089Func();
	cout << endl;
}

void B1089(void)
{
	B1089("data\\B1089-1.txt"); // 
}

