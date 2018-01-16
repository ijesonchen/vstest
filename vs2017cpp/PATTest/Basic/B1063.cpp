/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1063Func(void)
{
	return 0;
}


void B1063(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1063Func();
	cout << endl;
}

void B1063(void)
{
	B1063("data\\B1063-1.txt"); // 
}

