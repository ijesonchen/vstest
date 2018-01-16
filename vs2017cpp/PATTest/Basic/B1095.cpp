/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1095Func(void)
{
	return 0;
}


void B1095(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1095Func();
	cout << endl;
}

void B1095(void)
{
	B1095("data\\B1095-1.txt"); // 
}

