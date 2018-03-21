/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1024Func(void)
{
	return 0;
}


void B1024(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1024Func();
	cout << endl;
}

void B1024(void)
{
	B1024("data\\B1024-1.txt"); // 
}

