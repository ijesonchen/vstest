/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1054Func(void)
{
	return 0;
}


void B1054(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1054Func();
	cout << endl;
}

void B1054(void)
{
	B1054("data\\B1054-1.txt"); // 
}

