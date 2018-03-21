/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1088Func(void)
{
	return 0;
}


void B1088(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1088Func();
	cout << endl;
}

void B1088(void)
{
	B1088("data\\B1088-1.txt"); // 
}

