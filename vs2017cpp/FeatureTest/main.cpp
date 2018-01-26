#include <iostream>
#include <cstdlib>
#include "main.h"
#include <time.h>
#include <experimental/coroutine>


void TimeTest(void);
void ConsoleWindowControlTest(void);


using namespace std;
void main(void)
{
	ConsoleWindowControlTest();
	cout << "enter to continue" << endl;
	getchar();
}
