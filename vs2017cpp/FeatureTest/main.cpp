#include <iostream>
#include <string>
//#include <cstdlib>
#include "main.h"

void Test();


using namespace std;
void main(void)
{

	auto dmax = std::numeric_limits<double>::max();
	Test();


	cout << "enter to continue" << endl;
	string s;
	getline(cin, s);
//	getchar();
}
