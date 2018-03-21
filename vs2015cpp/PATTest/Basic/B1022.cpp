/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1022Func(void)
{
	return 0;
}


void B1022(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1022Func();
	cout << endl;
}

void B1022(void)
{
	B1022("data\\B1022-1.txt"); // 
}

