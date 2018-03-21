/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1044Func(void)
{
	return 0;
}


void T1044(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1044Func();
	cout << endl;
}

void T1044(void)
{
	T1044("data\\T1044-1.txt"); // 
}

