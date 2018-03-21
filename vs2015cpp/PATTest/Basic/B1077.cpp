/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int B1077Func(void)
{
	return 0;
}


void B1077(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	B1077Func();
	cout << endl;
}

void B1077(void)
{
	B1077("data\\B1077-1.txt"); // 
}

