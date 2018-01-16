/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1012Func(void)
{
	return 0;
}


void T1012(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1012Func();
	cout << endl;
}

void T1012(void)
{
	T1012("data\\T1012-1.txt"); // 
}

