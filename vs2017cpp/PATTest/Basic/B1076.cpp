/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1076Func(void)
{
	return 0;
}


void B1076(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1076Func();
	cout << endl;
}

void B1076(void)
{
	B1076("data\\B1076-1.txt"); // 
}

