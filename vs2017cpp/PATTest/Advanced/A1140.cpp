/*
1140. Look-and-say Sequence (20)
400 ms
65536 kB

Look-and-say sequence is a sequence of integers as the following:

D, D1, D111, D113, D11231, D112213111, ...
where D is in [0, 9] except 1. The (n+1)st number is a kind of description of the nth number. 
For example, the 2nd number means that there is one D in the 1st number, and hence it is D1; 
the 2nd number consists of one D (corresponding to D1) and one 1 (corresponding to 11), 
therefore the 3rd number is D111; or since 
the 4th number is D113, 
it consists of one D, two 1's, and one 3, so the next number must be D11231. 
This definition works for D = 1 as well. 
Now you are supposed to calculate the Nth number in a look-and-say sequence of a given digit D.

Input Specification:

Each input file contains one test case, which gives D (in [0, 9]) and a positive integer N (<=40), separated by a space.

Output Specification:

Print in a line the Nth number in a look-and-say sequence of D.

Sample Input:
1 8
Sample Output:
1123123111
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1140A
{
	vector<int> Next(const vector<int>& v)
	{
		vector<int> v2;
		int last = v.front();
		int cnt = 1;
		for (size_t i = 1; i < v.size(); ++i)
		{
			if (v[i] != last)
			{
				v2.push_back(last);
				v2.push_back(cnt);
				last = v[i];
				cnt = 1;
			}
			else
			{
				++cnt;
			}
		}
		v2.push_back(last);
		v2.push_back(cnt);
		return v2;
	}

	void Print(const vector<int>& v)
	{
		for (auto i : v)
		{
			cout << i;
		}
		cout << endl;
	}

	void main(void)
	{
		int d, n;
		cin >> d >> n;
		vector<int> v;
		v.push_back(d);
		for (int i = 1; i < n; ++i)
		{
			v = Next(v);
		}
		Print(v);
	}
}

// rename this to main int PAT
int A1140Func(void)
{
	nsA1140A::main();
	return 0;
}

void A1140(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1140Func();
	cout << endl;
}

void A1140(void)
{
	A1140("data\\A1140-1.txt"); // 
	A1140("data\\A1140-2.txt"); // 
}

