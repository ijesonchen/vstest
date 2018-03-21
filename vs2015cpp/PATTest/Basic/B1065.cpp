/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1065Func(void)
{
	return 0;
}


void B1065(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1065Func();
	cout << endl;
}

void B1065(void)
{
	B1065("data\\B1065-1.txt"); // 
}

