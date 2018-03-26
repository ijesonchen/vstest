#include <memory>
#include <array>
#include <iostream>
#include <vector>
#include <sstream>
//////////////////////////////////////////////////////////////////////////
/*
1. array length must be const
2. multi dimension array, try vector with vectors
3. init uniqu_ptr with char** p, then
	get() a char*** pp, p == *pp
	p == *sp
*/

using namespace std;

void VectorWithArrayTest(void)
{
	// 定长数组容器
	const int nArrayLen = 10;
	int nVecSize = 20;
	vector<array<char, nArrayLen>> va(nVecSize);
	unsigned idx = -1;
	for (auto& a : va)
	{
		for (auto& c : a)
		{
			c = ++idx % 16 + 'a';
		}
	}
	auto p = va.data(); // 第一个数组地址
	auto pp = p->data(); // 第一个数组地址
	auto pp2 = (p + 1)->data(); // 第二个数组地址
	auto pp3 = (p + 2)->data(); // 第二个数组地址
/*	
	内存从va.data()->data()开始，连续重复存放(16字符为一组）
	abcdefghijklmnopabcdefghijklmnop...
	arr1: abcdefghijk  arr2: klmnopabcd
*/
	cout << "done" << endl;
}

void ArrayTest(void)
{
	VectorWithArrayTest();

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

	vector<vector<unsigned char>> vv(length, vector<unsigned char>(length2));

	for (size_t i = 0; i < length; i++)
	{
		vv[i][i] = (int)i;
	}

	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < length2; j++)
		{
			vv[i][j] = i + j;
		}
	}


	int length3 = 4;
	vector<vector<vector<int>>> vvv(length, vector<vector<int>>(length2, vector<int>(length3)));


	for (size_t i = 0; i < length; i++)
	{
		vvv[i][i][i] = (int)i;
	}

	// char**: C++ to C lang
	// C++: vector<string> vs for memory management, vector<char*> vc for C interface
	// C: char** p = vc.data()

	vector<string> vvs;
	for (size_t i = 0; i < length; i++)
	{
		stringstream ss;
		ss << "teststr_" << i << "+" << i*i;
		vvs.push_back(ss.str());
	}

	vector<char*> vvc;
	for (auto& s : vvs)
	{
		vvc.push_back((char*)s.c_str());
	}

	auto ppc = vvc.data();
	for (size_t i = 0; i < length; i++)
	{
		cout << ppc[i] << endl;
	}

}