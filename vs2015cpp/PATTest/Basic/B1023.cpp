/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1023Func(void)
{
	return 0;
}


void B1023(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1023Func();
	cout << endl;
}

void B1023(void)
{
	B1023("data\\B1023-1.txt"); // 
}

