/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1039Func(void)
{
	return 0;
}


void B1039(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1039Func();
	cout << endl;
}

void B1039(void)
{
	B1039("data\\B1039-1.txt"); // 
}

