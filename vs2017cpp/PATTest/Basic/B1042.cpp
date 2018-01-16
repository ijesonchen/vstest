/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1042Func(void)
{
	return 0;
}


void B1042(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1042Func();
	cout << endl;
}

void B1042(void)
{
	B1042("data\\B1042-1.txt"); // 
}

