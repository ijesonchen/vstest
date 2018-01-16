/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1061Func(void)
{
	return 0;
}


void B1061(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1061Func();
	cout << endl;
}

void B1061(void)
{
	B1061("data\\B1061-1.txt"); // 
}

