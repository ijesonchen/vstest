/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1016Func(void)
{
	return 0;
}


void B1016(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1016Func();
	cout << endl;
}

void B1016(void)
{
	B1016("data\\B1016-1.txt"); // 
}

