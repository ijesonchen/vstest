/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1074Func(void)
{
	return 0;
}


void B1074(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1074Func();
	cout << endl;
}

void B1074(void)
{
	B1074("data\\B1074-1.txt"); // 
}

