#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int vvvv(void)
{
	int cnt = 0;
	int n = 0;
	cin >> cnt >> n;
	int first = n;

	int leftTemp = -1;
	int left = -1;
	int right = -1;
	int last = 0;
	bool enter = false;
	bool has0 = false;

	int maxCurrent = -1;
	int maxGlobal = 0;
	do
	{
		if (n == 0)
		{
			has0 = true;
		}
		if (maxCurrent > maxGlobal)
		{
			maxGlobal = maxCurrent;
			left = leftTemp;
			right = last;
		}
		maxCurrent += n;
		last = n;
		if (maxCurrent == n)
		{
			enter = false;
			leftTemp = n;
		}
		if (maxCurrent < 0)
		{
			enter = true;
			maxCurrent = 0;
		}
	} while (cin >> n);

	if (left == -1)
	{
		if (has0)
		{
			cout << "0 0 0" << endl;
		}
		else
		{
			cout << "0 " << first << " " << n << endl;
		}
	}
	else
	{
		cout << maxGlobal << " " << left << " " << right << endl;
	}

	return 0;
}