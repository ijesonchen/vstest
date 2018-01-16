/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1080Func(void)
{
	return 0;
}


void B1080(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1080Func();
	cout << endl;
}

void B1080(void)
{
	B1080("data\\B1080-1.txt"); // 
}

