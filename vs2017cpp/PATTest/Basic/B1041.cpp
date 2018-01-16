/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1041Func(void)
{
	return 0;
}


void B1041(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1041Func();
	cout << endl;
}

void B1041(void)
{
	B1041("data\\B1041-1.txt"); // 
}

