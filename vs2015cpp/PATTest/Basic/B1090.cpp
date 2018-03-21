/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1090Func(void)
{
	return 0;
}


void B1090(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1090Func();
	cout << endl;
}

void B1090(void)
{
	B1090("data\\B1090-1.txt"); // 
}

