/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1091Func(void)
{
	return 0;
}


void B1091(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1091Func();
	cout << endl;
}

void B1091(void)
{
	B1091("data\\B1091-1.txt"); // 
}

