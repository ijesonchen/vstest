/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1017Func(void)
{
	return 0;
}


void B1017(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1017Func();
	cout << endl;
}

void B1017(void)
{
	B1017("data\\B1017-1.txt"); // 
}

