/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1098Func(void)
{
	return 0;
}


void B1098(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1098Func();
	cout << endl;
}

void B1098(void)
{
	B1098("data\\B1098-1.txt"); // 
}

