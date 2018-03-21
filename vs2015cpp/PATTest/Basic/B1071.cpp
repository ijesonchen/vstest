/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1071Func(void)
{
	return 0;
}


void B1071(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1071Func();
	cout << endl;
}

void B1071(void)
{
	B1071("data\\B1071-1.txt"); // 
}

