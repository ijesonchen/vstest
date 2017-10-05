#include <memory>
#include <array>
#include <iostream>
#include <vector>
//////////////////////////////////////////////////////////////////////////
/*
1. array length must be const
2. multi dimension array, try vector with vectors
3. init uniqu_ptr with char** p, then
	get() a char*** pp, p == *pp
	p == *sp
*/

using namespace std;

void ArrayTest(void)
{
	int n = 5;
	// n must be const
	// array<int, n> is illegal
	array<int, 5> a = {};


	unsigned length = 4;
	unsigned length2 = 8;
	int** ssp = new int*[length];
	memset(ssp, 0, length * sizeof(int));
	for (size_t i = 0; i < length; i++)
	{
		auto p = new int[length2];
		cout << p << endl;
		memset(p, 0, length2 * sizeof(int));
		ssp[i] = p;
	}
	cout << endl;
	auto spssp = make_unique<int**>(ssp);
	
	auto rawssp = *spssp;
	auto rawssp2 = spssp.get();
	for (unsigned i = 0; i < length; ++i)
	{
		auto p = rawssp[i];

		cout << p << endl;
	}

	vector<vector<int>> vv(length, vector<int>(length2));

	for (size_t i = 0; i < length; i++)
	{
		vv[i][i] = (int)i;
	}

	int length3 = 4;
	vector<vector<vector<int>>> vvv(length, vector<vector<int>>(length2, vector<int>(length3)));


	for (size_t i = 0; i < length; i++)
	{
		vvv[i][i][i] = (int)i;
	}
}