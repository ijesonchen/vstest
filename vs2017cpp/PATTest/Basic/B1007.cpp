/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1007Func(void)
{
	return 0;
}


void B1007(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1007Func();
	cout << endl;
}

void B1007(void)
{
	B1007("data\\B1007-1.txt"); // 
}

