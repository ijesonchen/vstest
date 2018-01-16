/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1002Func(void)
{
	return 0;
}


void B1002(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1002Func();
	cout << endl;
}

void B1002(void)
{
	B1002("data\\B1002-1.txt"); // 
}

