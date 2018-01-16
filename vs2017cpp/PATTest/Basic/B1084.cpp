/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1084Func(void)
{
	return 0;
}


void B1084(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1084Func();
	cout << endl;
}

void B1084(void)
{
	B1084("data\\B1084-1.txt"); // 
}

