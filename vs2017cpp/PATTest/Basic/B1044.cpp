/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1044Func(void)
{
	return 0;
}


void B1044(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1044Func();
	cout << endl;
}

void B1044(void)
{
	B1044("data\\B1044-1.txt"); // 
}

