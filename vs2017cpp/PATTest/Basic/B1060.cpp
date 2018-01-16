/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1060Func(void)
{
	return 0;
}


void B1060(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1060Func();
	cout << endl;
}

void B1060(void)
{
	B1060("data\\B1060-1.txt"); // 
}

