/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1020Func(void)
{
	return 0;
}


void B1020(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1020Func();
	cout << endl;
}

void B1020(void)
{
	B1020("data\\B1020-1.txt"); // 
}

