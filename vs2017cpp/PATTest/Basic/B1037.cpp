/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1037Func(void)
{
	return 0;
}


void B1037(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1037Func();
	cout << endl;
}

void B1037(void)
{
	B1037("data\\B1037-1.txt"); // 
}

