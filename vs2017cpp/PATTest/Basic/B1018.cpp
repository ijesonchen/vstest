/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1018Func(void)
{
	return 0;
}


void B1018(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1018Func();
	cout << endl;
}

void B1018(void)
{
	B1018("data\\B1018-1.txt"); // 
}

