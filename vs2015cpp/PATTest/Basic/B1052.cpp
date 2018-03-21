/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1052Func(void)
{
	return 0;
}


void B1052(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1052Func();
	cout << endl;
}

void B1052(void)
{
	B1052("data\\B1052-1.txt"); // 
}

