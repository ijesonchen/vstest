/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1050Func(void)
{
	return 0;
}


void B1050(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1050Func();
	cout << endl;
}

void B1050(void)
{
	B1050("data\\B1050-1.txt"); // 
}

