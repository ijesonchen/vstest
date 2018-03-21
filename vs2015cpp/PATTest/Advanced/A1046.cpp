/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1046Func(void)
{
	return 0;
}


void A1046(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1046Func();
	cout << endl;
}

void A1046(void)
{
	A1046("data\\A1046-1.txt"); // 
}

