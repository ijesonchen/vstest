/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1028Func(void)
{
	return 0;
}


void A1028(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1028Func();
	cout << endl;
}

void A1028(void)
{
	A1028("data\\A1028-1.txt"); // 
}

