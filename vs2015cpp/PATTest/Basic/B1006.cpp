/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1006Func(void)
{
	return 0;
}


void B1006(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1006Func();
	cout << endl;
}

void B1006(void)
{
	B1006("data\\B1006-1.txt"); // 
}

