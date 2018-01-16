/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1053Func(void)
{
	return 0;
}


void B1053(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1053Func();
	cout << endl;
}

void B1053(void)
{
	B1053("data\\B1053-1.txt"); // 
}

