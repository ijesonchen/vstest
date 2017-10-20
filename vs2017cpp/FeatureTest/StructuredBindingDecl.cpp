/*
** language feature 'structured bindings' requires compiler flag '/std:c++latest'
config property, C/C++, Language:
    C++ Language Standard: ISO C++ Latest Draft Standard (/std:c++latest)

Structured binding declaration (since C++17)
C++  C++ language  Declarations
Binds the specified names to subobjects or elements of the initializer.

attr(optional) cv-auto ref-operator(optional) [ identifier-list ] = expression ;	(1)	(since C++17)
attr(optional) cv-auto ref-operator(optional) [ identifier-list ] { expression } ;	(2)	(since C++17)
attr(optional) cv-auto ref-operator(optional) [ identifier-list ] ( expression ) ;	(3)	(since C++17)

cv-auto: const/volatile/auto
ref-operator: & / && 
*/

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

tuple<int, string> SBDTest(int a)
{
	return make_tuple(a*a, "teststr");
}

void TestStructuredBindingsDeclaration(void)
{
	auto[x, y] = SBDTest(2);
	cout << x << " " << y << endl;
}