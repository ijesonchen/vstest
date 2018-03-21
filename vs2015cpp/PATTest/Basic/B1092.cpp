/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1092Func(void)
{
	return 0;
}


void B1092(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1092Func();
	cout << endl;
}

void B1092(void)
{
	B1092("data\\B1092-1.txt"); // 
}

