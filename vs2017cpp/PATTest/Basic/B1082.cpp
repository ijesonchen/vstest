/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1082Func(void)
{
	return 0;
}


void B1082(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1082Func();
	cout << endl;
}

void B1082(void)
{
	B1082("data\\B1082-1.txt"); // 
}

