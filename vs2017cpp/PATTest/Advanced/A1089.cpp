/*
1089. Insert or Merge (25)
200 ms
65536 kB

According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
Each iteration, insertion sort removes one element from the input data, 
finds the location it belongs within the sorted list, and inserts it there. 
It repeats until no input elements remain.

Merge sort works as follows: Divide the unsorted list into N sublists, 
each containing 1 element (a list of 1 element is considered sorted). 
Then repeatedly merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, 
can you tell which sorting method we are using?

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N (<=100).
Then in the next line, N integers are given as the initial sequence.
The last line contains the partially sorted sequence of the N numbers.
It is assumed that the target sequence is always ascending. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in the first line either "Insertion Sort" or "Merge Sort" 
to indicate the method used to obtain the partial result. 
Then run this method for one more iteration and output in the second line the resulting sequence. 
It is guaranteed that the answer is unique for each test case. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:
Merge Sort
1 2 3 8 4 5 7 9 0 6
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
15:25
判断是插入还是归并排序的步骤
实现下一步

ins判断(merge抛异常)
15:55 11/25 异常
*/

namespace nsA1089A
{
	int nTotal = 0;
	vector<int> vInit;
	vector<int> vRef;

	void Print(const vector<int>& v)
	{
		cout << v.front();
		for (size_t i = 1; i < v.size(); ++i)
		{
			cout << " " << v[i];
		}
		cout << endl;
	}

	int SortIndex(int start, int len)
	{
		int a = vRef[start];
		for (++start; start < len; ++start)
		{
			if (vRef[start] < a)
			{
				break;
			}
			a = vRef[start];
		}
		return start-1;
	}

	bool SameTail(int start)
	{
		for (int i = start; i < nTotal; ++i)
		{
			if (vInit[i] != vRef[i])
			{
				return false;
			}
		}
		return true;
	}

	bool IsInsertion(void)
	{
		int start = SortIndex(0, nTotal);
		if (!SameTail(start + 1))
		{
			return false;
		}
		sort(vRef.begin(), vRef.begin() + start + 2);
		cout << "Insertion Sort" << endl;
		Print(vRef);
		return true;
	}

	int MergeStep(void)
	{
		vector<int> vMerge = vInit;
		int step = 4;
		bool same = true;
		for (; step < nTotal && same; step *=2)
		{
			sort(vMerge.begin(), vMerge.begin() + step);
			for (int i = 0; i < step; ++i)
			{
				if (vMerge[i] != vRef[i])
				{
					same = false;
					break;
				}
			}
		}
		return step / 2;
	}

	void Merge(void)
	{
		int step = MergeStep();
		for (int i = 0; i < nTotal; i+= step)
		{
			int off = i + step;
			if (off > nTotal)
			{
				off = nTotal;
			}
			sort(vRef.begin() + i, vRef.begin() + off);
		}
		cout << "Merge Sort" << endl;
		Print(vRef);
	}

	void main(void)
	{
		cin >> nTotal;
		vInit.resize(nTotal);
		vRef.resize(nTotal);
		for (int i = 0; i < nTotal; ++i)
		{
			cin >> vInit[i];
		}
		for (int i = 0; i < nTotal; ++i)
		{
			cin >> vRef[i];
		}
		if (IsInsertion())
		{
			return;
		}

		Merge();
	}
}

// rename this to main int PAT
int A1089Func(void)
{
	nsA1089A::main();
	return 0;
}


void A1089(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1089Func();
	cout << endl;
}

void A1089(void)
{
//	A1089("data\\A1089-1.txt"); // 
	A1089("data\\A1089-2.txt"); // 
}

