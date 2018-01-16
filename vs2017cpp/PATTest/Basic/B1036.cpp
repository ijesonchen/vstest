/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1036Func(void)
{
	return 0;
}


void B1036(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1036Func();
	cout << endl;
}

void B1036(void)
{
	B1036("data\\B1036-1.txt"); // 
}

