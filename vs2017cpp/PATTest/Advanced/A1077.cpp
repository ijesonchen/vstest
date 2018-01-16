/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1077Func(void)
{
	return 0;
}


void A1077(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1077Func();
	cout << endl;
}

void A1077(void)
{
	A1077("data\\A1077-1.txt"); // 
}

