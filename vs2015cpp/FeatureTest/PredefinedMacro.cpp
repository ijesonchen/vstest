#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////
/* x64 debug
PredefinedMacro from CPP standard
__FILE__     : PredefinedMacro.cpp
__LINE__     : 21
__DATE__     : Jun 25 2017
__TIME__     : 17:09:04
__FUNCTION__ : PredefinedMacro
__FUNCTION__ not found in c++17 prestandard, but both supported in vs & g++
In vs2015 and C++17 pre standard, __func__ is defined, but vs2013 not supported.
__func__ is an implementation-defined string, can be used after a function is defined.
MyStruct::MyStruct
enter to continue

NOTE: x32 debug, not x32 release
__FILE__     : c:\users\jeson\documents\github\vs2013\vs2013cpp\featuretest\predefinedmacro.cpp
*/

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