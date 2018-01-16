/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1049Func(void)
{
	return 0;
}


void B1049(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1049Func();
	cout << endl;
}

void B1049(void)
{
	B1049("data\\B1049-1.txt"); // 
}

