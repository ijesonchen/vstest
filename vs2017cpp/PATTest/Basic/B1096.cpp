/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1096Func(void)
{
	return 0;
}


void B1096(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1096Func();
	cout << endl;
}

void B1096(void)
{
	B1096("data\\B1096-1.txt"); // 
}

