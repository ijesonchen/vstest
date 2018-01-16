/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1050Func(void)
{
	return 0;
}


void T1050(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1050Func();
	cout << endl;
}

void T1050(void)
{
	T1050("data\\T1050-1.txt"); // 
}

