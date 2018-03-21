/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1021Func(void)
{
	return 0;
}


void B1021(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1021Func();
	cout << endl;
}

void B1021(void)
{
	B1021("data\\B1021-1.txt"); // 
}

