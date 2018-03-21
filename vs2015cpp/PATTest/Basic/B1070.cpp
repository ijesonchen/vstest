/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1070Func(void)
{
	return 0;
}


void B1070(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1070Func();
	cout << endl;
}

void B1070(void)
{
	B1070("data\\B1070-1.txt"); // 
}

