/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1093Func(void)
{
	return 0;
}


void B1093(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1093Func();
	cout << endl;
}

void B1093(void)
{
	B1093("data\\B1093-1.txt"); // 
}

