/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1068Func(void)
{
	return 0;
}


void B1068(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1068Func();
	cout << endl;
}

void B1068(void)
{
	B1068("data\\B1068-1.txt"); // 
}

