/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1038Func(void)
{
	return 0;
}


void A1038(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1038Func();
	cout << endl;
}

void A1038(void)
{
	A1038("data\\A1038-1.txt"); // 
}

