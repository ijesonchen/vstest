#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std;

void main(int argc, char** argv)
{
	int msSleep = 1000;
	if (argc >= 2)
	{
		msSleep = atoi(argv[1]);
	}
	this_thread::sleep_for(chrono::milliseconds(msSleep));
}