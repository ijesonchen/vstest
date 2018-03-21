/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1011Func(void)
{
	return 0;
}


void B1011(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1011Func();
	cout << endl;
}

void B1011(void)
{
	B1011("data\\B1011-1.txt"); // 
}

