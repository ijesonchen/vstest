/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1043Func(void)
{
	return 0;
}


void B1043(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1043Func();
	cout << endl;
}

void B1043(void)
{
	B1043("data\\B1043-1.txt"); // 
}

