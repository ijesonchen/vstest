/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1014Func(void)
{
	return 0;
}


void B1014(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1014Func();
	cout << endl;
}

void B1014(void)
{
	B1014("data\\B1014-1.txt"); // 
}

