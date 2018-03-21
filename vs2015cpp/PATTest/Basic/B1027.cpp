/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1027Func(void)
{
	return 0;
}


void B1027(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1027Func();
	cout << endl;
}

void B1027(void)
{
	B1027("data\\B1027-1.txt"); // 
}

