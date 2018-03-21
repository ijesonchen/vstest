/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1075Func(void)
{
	return 0;
}


void B1075(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1075Func();
	cout << endl;
}

void B1075(void)
{
	B1075("data\\B1075-1.txt"); // 
}

