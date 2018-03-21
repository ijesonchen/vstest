/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1086Func(void)
{
	return 0;
}


void B1086(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1086Func();
	cout << endl;
}

void B1086(void)
{
	B1086("data\\B1086-1.txt"); // 
}

