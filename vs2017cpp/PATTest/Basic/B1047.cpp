/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1047Func(void)
{
	return 0;
}


void B1047(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1047Func();
	cout << endl;
}

void B1047(void)
{
	B1047("data\\B1047-1.txt"); // 
}

