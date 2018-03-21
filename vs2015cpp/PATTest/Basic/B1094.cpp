/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1094Func(void)
{
	return 0;
}


void B1094(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1094Func();
	cout << endl;
}

void B1094(void)
{
	B1094("data\\B1094-1.txt"); // 
}

