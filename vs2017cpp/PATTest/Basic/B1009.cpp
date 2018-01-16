/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1009Func(void)
{
	return 0;
}


void B1009(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1009Func();
	cout << endl;
}

void B1009(void)
{
	B1009("data\\B1009-1.txt"); // 
}

