/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1044Func(void)
{
	return 0;
}


void A1044(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1044Func();
	cout << endl;
}

void A1044(void)
{
	A1044("data\\A1044-1.txt"); // 
}

