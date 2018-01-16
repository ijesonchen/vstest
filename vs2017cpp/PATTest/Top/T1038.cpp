/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1038Func(void)
{
	return 0;
}


void T1038(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1038Func();
	cout << endl;
}

void T1038(void)
{
	T1038("data\\T1038-1.txt"); // 
}

