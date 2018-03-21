/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1057Func(void)
{
	return 0;
}


void B1057(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1057Func();
	cout << endl;
}

void B1057(void)
{
	B1057("data\\B1057-1.txt"); // 
}

