/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1085Func(void)
{
	return 0;
}


void B1085(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1085Func();
	cout << endl;
}

void B1085(void)
{
	B1085("data\\B1085-1.txt"); // 
}

