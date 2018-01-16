/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1031Func(void)
{
	return 0;
}


void B1031(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1031Func();
	cout << endl;
}

void B1031(void)
{
	B1031("data\\B1031-1.txt"); // 
}

