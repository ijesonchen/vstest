/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1066Func(void)
{
	return 0;
}


void B1066(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1066Func();
	cout << endl;
}

void B1066(void)
{
	B1066("data\\B1066-1.txt"); // 
}

