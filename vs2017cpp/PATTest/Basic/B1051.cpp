/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1051Func(void)
{
	return 0;
}


void B1051(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1051Func();
	cout << endl;
}

void B1051(void)
{
	B1051("data\\B1051-1.txt"); // 
}

