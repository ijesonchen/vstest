/*

*/

#include "patMain.h"
#include <iostream>

using namespace std;

int A1136Func(void)
{
	return 0;
}


void A1136(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1136Func();
}

void A1136(void)
{
	A1136("data\\A1136-1.TXT"); // 
}

