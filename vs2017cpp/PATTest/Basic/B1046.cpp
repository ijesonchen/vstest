/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1046Func(void)
{
	return 0;
}


void B1046(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1046Func();
	cout << endl;
}

void B1046(void)
{
	B1046("data\\B1046-1.txt"); // 
}

