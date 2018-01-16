/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1081Func(void)
{
	return 0;
}


void B1081(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1081Func();
	cout << endl;
}

void B1081(void)
{
	B1081("data\\B1081-1.txt"); // 
}

