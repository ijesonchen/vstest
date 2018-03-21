/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1034Func(void)
{
	return 0;
}


void B1034(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1034Func();
	cout << endl;
}

void B1034(void)
{
	B1034("data\\B1034-1.txt"); // 
}

