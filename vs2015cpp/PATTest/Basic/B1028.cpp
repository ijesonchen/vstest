/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1028Func(void)
{
	return 0;
}


void B1028(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1028Func();
	cout << endl;
}

void B1028(void)
{
	B1028("data\\B1028-1.txt"); // 
}

