/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1145Func(void)
{
	return 0;
}


void A1145(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1145Func();
	cout << endl;
}

void A1145(void)
{
	A1145("data\\A1145-1.txt"); // 
}

