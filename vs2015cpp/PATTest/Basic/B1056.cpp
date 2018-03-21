/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1056Func(void)
{
	return 0;
}


void B1056(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1056Func();
	cout << endl;
}

void B1056(void)
{
	B1056("data\\B1056-1.txt"); // 
}

