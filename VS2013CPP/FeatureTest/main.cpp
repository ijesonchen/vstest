#include <iostream>
#include <cstdlib>
#include "main.h"

using namespace std;

auto pIncTextFile = R"(
#include "svnrel.txt"
)";

void main(void)
{
	cout << pIncTextFile << endl;
	cout << "enter to continue" << endl;
	getchar();
}