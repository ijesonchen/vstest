/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1053Func(void)
{
	return 0;
}


void A1053(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1053Func();
	cout << endl;
}

void A1053(void)
{
	A1053("data\\A1053-1.txt"); // 
}

