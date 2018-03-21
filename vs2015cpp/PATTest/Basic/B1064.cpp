/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1064Func(void)
{
	return 0;
}


void B1064(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1064Func();
	cout << endl;
}

void B1064(void)
{
	B1064("data\\B1064-1.txt"); // 
}

