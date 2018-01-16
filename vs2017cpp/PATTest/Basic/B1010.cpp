/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1010Func(void)
{
	return 0;
}


void B1010(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1010Func();
	cout << endl;
}

void B1010(void)
{
	B1010("data\\B1010-1.txt"); // 
}

