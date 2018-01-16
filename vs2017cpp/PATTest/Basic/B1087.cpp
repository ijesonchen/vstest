/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1087Func(void)
{
	return 0;
}


void B1087(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1087Func();
	cout << endl;
}

void B1087(void)
{
	B1087("data\\B1087-1.txt"); // 
}

