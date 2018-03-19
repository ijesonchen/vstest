#include <limits>
#include <iostream>

using namespace std;

void MaxTest(void)
{
	int x = 0;
	const float y = std::numeric_limits<decltype(x)>::max();
	cout << y << endl;
}