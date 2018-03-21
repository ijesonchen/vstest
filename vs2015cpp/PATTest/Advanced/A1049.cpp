/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1049Func(void)
{
	return 0;
}


void A1049(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1049Func();
	cout << endl;
}

void A1049(void)
{
	A1049("data\\A1049-1.txt"); // 
}

