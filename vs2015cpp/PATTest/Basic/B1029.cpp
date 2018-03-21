/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1029Func(void)
{
	return 0;
}


void B1029(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1029Func();
	cout << endl;
}

void B1029(void)
{
	B1029("data\\B1029-1.txt"); // 
}

