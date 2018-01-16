/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1078Func(void)
{
	return 0;
}


void A1078(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1078Func();
	cout << endl;
}

void A1078(void)
{
	A1078("data\\A1078-1.txt"); // 
}

