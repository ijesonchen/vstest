/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1058Func(void)
{
	return 0;
}


void B1058(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1058Func();
	cout << endl;
}

void B1058(void)
{
	B1058("data\\B1058-1.txt"); // 
}

