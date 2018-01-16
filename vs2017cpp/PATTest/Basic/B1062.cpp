/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1062Func(void)
{
	return 0;
}


void B1062(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1062Func();
	cout << endl;
}

void B1062(void)
{
	B1062("data\\B1062-1.txt"); // 
}

