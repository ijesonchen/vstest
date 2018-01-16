/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1019Func(void)
{
	return 0;
}


void A1019(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1019Func();
	cout << endl;
}

void A1019(void)
{
	A1019("data\\A1019-1.txt"); // 
}

