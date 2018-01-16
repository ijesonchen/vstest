/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1005Func(void)
{
	return 0;
}


void B1005(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1005Func();
	cout << endl;
}

void B1005(void)
{
	B1005("data\\B1005-1.txt"); // 
}

