/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1048Func(void)
{
	return 0;
}


void B1048(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1048Func();
	cout << endl;
}

void B1048(void)
{
	B1048("data\\B1048-1.txt"); // 
}

