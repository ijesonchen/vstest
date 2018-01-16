/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1059Func(void)
{
	return 0;
}


void B1059(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1059Func();
	cout << endl;
}

void B1059(void)
{
	B1059("data\\B1059-1.txt"); // 
}

