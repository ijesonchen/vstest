/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1025Func(void)
{
	return 0;
}


void B1025(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1025Func();
	cout << endl;
}

void B1025(void)
{
	B1025("data\\B1025-1.txt"); // 
}

