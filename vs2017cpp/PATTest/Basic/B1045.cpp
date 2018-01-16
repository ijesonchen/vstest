/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1045Func(void)
{
	return 0;
}


void B1045(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1045Func();
	cout << endl;
}

void B1045(void)
{
	B1045("data\\B1045-1.txt"); // 
}

