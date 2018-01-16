/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1055Func(void)
{
	return 0;
}


void B1055(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1055Func();
	cout << endl;
}

void B1055(void)
{
	B1055("data\\B1055-1.txt"); // 
}

