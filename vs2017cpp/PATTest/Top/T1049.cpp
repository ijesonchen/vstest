/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1049Func(void)
{
	return 0;
}


void T1049(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1049Func();
	cout << endl;
}

void T1049(void)
{
	T1049("data\\T1049-1.txt"); // 
}

