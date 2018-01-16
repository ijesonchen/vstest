/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1023Func(void)
{
	return 0;
}


void T1023(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1023Func();
	cout << endl;
}

void T1023(void)
{
	T1023("data\\T1023-1.txt"); // 
}

