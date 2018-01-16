/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1092Func(void)
{
	return 0;
}


void A1092(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1092Func();
	cout << endl;
}

void A1092(void)
{
	A1092("data\\A1092-1.txt"); // 
}

