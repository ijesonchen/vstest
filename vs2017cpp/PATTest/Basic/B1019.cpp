/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1019Func(void)
{
	return 0;
}


void B1019(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1019Func();
	cout << endl;
}

void B1019(void)
{
	B1019("data\\B1019-1.txt"); // 
}

