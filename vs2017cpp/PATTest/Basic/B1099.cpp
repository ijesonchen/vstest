/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1099Func(void)
{
	return 0;
}


void B1099(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1099Func();
	cout << endl;
}

void B1099(void)
{
	B1099("data\\B1099-1.txt"); // 
}

