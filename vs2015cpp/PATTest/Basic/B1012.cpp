/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1012Func(void)
{
	return 0;
}


void B1012(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1012Func();
	cout << endl;
}

void B1012(void)
{
	B1012("data\\B1012-1.txt"); // 
}

