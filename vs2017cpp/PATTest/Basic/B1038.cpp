/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1038Func(void)
{
	return 0;
}


void B1038(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1038Func();
	cout << endl;
}

void B1038(void)
{
	B1038("data\\B1038-1.txt"); // 
}

