/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1078Func(void)
{
	return 0;
}


void B1078(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1078Func();
	cout << endl;
}

void B1078(void)
{
	B1078("data\\B1078-1.txt"); // 
}

