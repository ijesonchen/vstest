#include <iostream>
#include <cstdlib>
#include "main.h"
#include <time.h>
#include <experimental/coroutine>


void TimeTest(void);


using namespace std;
void main(void)
{
	TimeTest();
	cout << "enter to continue" << endl;
	getchar();
}
