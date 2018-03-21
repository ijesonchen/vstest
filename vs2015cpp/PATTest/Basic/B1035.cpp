/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1035Func(void)
{
	return 0;
}


void B1035(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1035Func();
	cout << endl;
}

void B1035(void)
{
	B1035("data\\B1035-1.txt"); // 
}

