/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1079Func(void)
{
	return 0;
}


void B1079(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1079Func();
	cout << endl;
}

void B1079(void)
{
	B1079("data\\B1079-1.txt"); // 
}

