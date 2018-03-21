/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1015Func(void)
{
	return 0;
}


void B1015(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1015Func();
	cout << endl;
}

void B1015(void)
{
	B1015("data\\B1015-1.txt"); // 
}

