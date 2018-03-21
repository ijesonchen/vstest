/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1072Func(void)
{
	return 0;
}


void B1072(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1072Func();
	cout << endl;
}

void B1072(void)
{
	B1072("data\\B1072-1.txt"); // 
}

