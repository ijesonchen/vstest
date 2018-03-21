/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1032Func(void)
{
	return 0;
}


void B1032(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1032Func();
	cout << endl;
}

void B1032(void)
{
	B1032("data\\B1032-1.txt"); // 
}

