/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1073Func(void)
{
	return 0;
}


void B1073(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1073Func();
	cout << endl;
}

void B1073(void)
{
	B1073("data\\B1073-1.txt"); // 
}

