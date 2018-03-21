/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1085Func(void)
{
	return 0;
}


void A1085(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1085Func();
	cout << endl;
}

void A1085(void)
{
	A1085("data\\A1085-1.txt"); // 
}

