/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1069Func(void)
{
	return 0;
}


void B1069(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1069Func();
	cout << endl;
}

void B1069(void)
{
	B1069("data\\B1069-1.txt"); // 
}

