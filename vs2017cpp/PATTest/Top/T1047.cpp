/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1047Func(void)
{
	return 0;
}


void T1047(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1047Func();
	cout << endl;
}

void T1047(void)
{
	T1047("data\\T1047-1.txt"); // 
}

