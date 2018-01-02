/*
1009. Product of Polynomials (25)
cost: 40min

This time, you are supposed to find A*B where A and B 
are two polynomials.

Input Specification:

Each input file contains one test case. Each case occupies 
2 lines, and each line contains the information of a 
polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number 
of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) 
are the exponents and coefficients, respectively. It is 
given that 1 <= K <= 10, 0 <= NK < ... < N2 < N1 <=1000.

Output Specification:

For each test case you should output the product of A and B 
in one line, with the same format as the input. Notice that 
there must be NO extra space at the end of each line. Please 
be accurate up to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 3 3.6 2 6.0 1 1.6
*/


#include "..\patMain.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// rename this to main int PAT

void A1009Read(map<int, float>& A)
{
	int k, n;
	float a;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cin >> n >> a;
		A[n] = a;
	}
}

int A1009Func(void)
{
	map<int, float> A,B,C;
	A1009Read(A);
	A1009Read(B);

	for (auto& a : A)
	{
		for (auto& b : B)
		{
			C[a.first + b.first] += a.second * b.second;
		}
	}
	char buf[100] = { 0 };
	vector<int> vn;
	vector<string> va;
	for (auto it = C.rbegin(); it != C.rend(); ++it)
	{
		sprintf(buf, "%.1f", it->second);
		string s = buf;
		if (s == "0.0" || s == "-0.0")
		{
			continue;
		}
		vn.push_back(it->first);
		va.push_back(s);
	}

	cout << vn.size();
	int len = (int)vn.size();
	for (int i = 0; i < len; ++i)
	{
		cout << " " << vn[i] << " " << va[i];
	}

	return 0;
}


void A1009(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1009Func();
	cout << endl;
}

void A1009(void)
{
	A1009("data\\A1009-1.txt"); // 3 3 3.6 2 6.0 1 1.6
	A1009("data\\A1009-2.txt"); // 2 4 4.0 2 -9.0
	A1009("data\\A1009-3.txt"); // 2 4 0.2 2 -0.2 // 3 4 0.2 3 -0.04 2 -0.16
	A1009("data\\A1009-4.txt"); // 2 4 0.2 2 -0.2 // 3 4 0.2 3  0.04 2 -0.16
}