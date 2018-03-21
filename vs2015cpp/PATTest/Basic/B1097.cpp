/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1097Func(void)
{
	return 0;
}


void B1097(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1097Func();
	cout << endl;
}

void B1097(void)
{
	B1097("data\\B1097-1.txt"); // 
}

