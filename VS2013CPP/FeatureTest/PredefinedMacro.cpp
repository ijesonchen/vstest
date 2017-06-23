#include <iostream>
#include <string>

using namespace std;

struct MyStruct
{
	MyStruct() :s(__FUNCTION__) {}
	void Test()
	{
		cout << s << endl;
	}

	string s;
};

void PredefinedMacro(void)
{
	cout << "PredefinedMacro from CPP standard" << endl;
	cout << "__FILE__     : " << __FILE__ << endl;
	cout << "__LINE__     : " << __LINE__ << endl;
	cout << "__DATE__     : " << __DATE__ << endl;
	cout << "__TIME__     : " << __TIME__ << endl;
	cout << "__FUNCTION__ : " << __FUNCTION__ << endl;
	cout << "__FUNCTION__ not found in c++17 prestandard, but both supported in vs & g++" << endl;
	cout << "In vs2015 and C++17 pre standard, __func__ is defined, but vs2013 not supported." << endl;
	cout << "__func__ is an implementation-defined string, can be used after a function is defined." << endl;
	MyStruct().Test();
}