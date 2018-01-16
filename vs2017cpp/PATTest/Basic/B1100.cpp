/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1100Func(void)
{
	return 0;
}


void B1100(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1100Func();
	cout << endl;
}

void B1100(void)
{
	B1100("data\\B1100-1.txt"); // 
}

