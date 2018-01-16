/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1028Func(void)
{
	return 0;
}


void T1028(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1028Func();
	cout << endl;
}

void T1028(void)
{
	T1028("data\\T1028-1.txt"); // 
}

