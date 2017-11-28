/*
ans:
17/17/25
hint:
coefficients of result may be zero, remove it from map

This time, you are supposed to find A+B where A and B are two polynomials.

Input

Each input file contains one test case. Each case occupies 2 lines, and each 
line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, 
where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) 
are the exponents and coefficients, respectively. It is given that 1 <= K <= 10£¬
0 <= NK < ... < N2 < N1 <=1000.

Output

For each test case you should output the sum of A and B in one line, with the 
same format as the input. Notice that there must be NO extra space at the end 
of each line. Please be accurate to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 2 1.5 1 2.9 0 3.2
*/

#include <iostream>
#include <cstdio>
#include <map>
using namespace std;



void A1002(void)
{
	int n = 0;
	int k = 0;
	double a = 0;
	map<int, double> res;
	for (int i = 0; i < 2; ++i)
	{
		cin >> n;
		for (int j = 0; j < n; ++j)
		{
			cin >> k >> a;
			res[k] += a;
		}
	}
	int cnt = 0;
	for (map<int, double>::reverse_iterator it = res.rbegin();
		it != res.rend();
		++it)
	{
		if (it->second == 0)
		{
			continue;
		}
		++cnt;
	}

	cout << cnt;
	for (map<int, double>::reverse_iterator it = res.rbegin();
		it != res.rend();
		++it)
	{
		if (it->second == 0)
		{
			continue;
		}
		printf(" %d %.1lf", it->first, it->second);
	}
}