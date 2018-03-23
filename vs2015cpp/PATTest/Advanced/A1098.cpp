/*
1098. Insertion or Heap Sort (25)
100 ms
65536 kB

�ܽ᣺
	1. ����������ܴ����м䲿����������������Ҫ����������������򳤶���򵥣�
	2. ����ӽ����֣����Ƕ�ʱ��û�н����Ӧ���ݻ�����Ϊ��ȷ�����ĵ�Ҫ���ͨ��


20min 11/25, 20min 23/25, 15min 23/25��20MIN pass

15��50
�жϲ�������/������

1. �Ƿ���룿����Ϊ��
���жϲ��루���򷵻ط�0��
16��10 11/25 ��01��3��5 �쳣2

�ж�Heap
16:30 23/25 wa2

ֻ�ж�heap
16��33 12/25 ��0 0,2,4

2ӦΪinsert
16��45 �����ٽ�tc��3-6����δ�ҵ�����
���ԣ�vRefȷ��δ�������

14��30
�Ľ��� ����sortģ��insert
14��40 23/25 wa2
ʹ��A1089��insert�ж��㷨����ͨ��PT0,2,4

���⣺insertion����������������ʱ��������������
A1098::IsInsertion/IsInsertion2���ǰ�������Ĳ������
A1089::IsInsertion���ǰ��������Ĳ��������

A1098::IsInsertion2
bug-fix-1��������ǰ�����򲿷�
14:50 PASS

�磺
2 0 1 3 4 5 7 6 ԭʼ
0 2 1 3 4 5 7 6 �ο�1
0 1 2 3 4 5 7 6 �ο�2����Ŀ�����Ĳο�
0 1 2 3 4 5 6 7 �ο�3����Ŀ��Ҫ�Ľ��

�ο�2���ο�3�Ĳ��裬�м����������õ�3 4 5 7
A1089::IsIns: ������ǰ�����򲿷�(�����ࣩܶ���ٱȽ�β���Ƿ���ȣ���ȷ����λ��7
A1098::IsIns: ������������ͬ����(�����ࣩܶ���ڱȽ�ǰ���Ƿ�������ȷ����λ��3
A1098::IsIns2:��λ��1��ʼ����ֱ���Ͳο���ȣ��������磩����ʱ��λ��3
bug-fix-1������������ȵ����򣨾�������������ʱ��λ��7
���ȷ��λ��3����һ������������Ȼ�ǲο�2
���ȷ��λ��7����һ�������������ο�3


According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
At each iteration, insertion sort removes one element from the input data, 
finds the location it belongs within the sorted list, and inserts it there. 
It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region,
and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. 
it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, 
can you tell which sorting method we are using?

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). 
Then in the next line, N integers are given as the initial sequence. 
The last line contains the partially sorted sequence of the N numbers.
It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to 
indicate the method used to obtain the partial result.
Then run this method for one more iteration and output in the second line the resuling sequence.
It is guaranteed that the answer is unique for each test case.
All the numbers in a line must be separated by a space, 
and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

namespace nsA1098A
{
	int nTotal;
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

	bool IsInsertion2(void)
	{
		vector<int> vTemp(vInit);

		for (size_t i = 1; i < vTemp.size(); ++i)
		{
			sort(vTemp.begin(), vTemp.begin() + i);
//			Print(vTemp);
			if (vTemp == vRef)
			{
				// bug-fix-1: ������ǰ�����򲿷�
				while (vTemp == vRef)
				{
					++i;
					sort(vTemp.begin(), vTemp.begin() + i);
				}
				cout << "Insertion Sort" << endl;
//				sort(vTemp.begin(), vTemp.begin() + i + 1);
				Print(vTemp);
				return true;
			}
		}
		return false;
	}

	bool SameTail(int n)
	{
		for (int i = n; i < nTotal; ++i)
		{
			if (vInit[i] != vRef[i])
			{
				return false;
			}
		}
		return true;
	}

	int InsertStep(void)
	{
		// same tail
		int step = step = nTotal - 1;
		for (; step >= 0; --step)
		{
			if (!SameTail(step))
			{
				break;
			}
		}
		return step + 1;
	}

	bool IsInsertion(void)
	{
		int step = InsertStep();
		if (step <= 0)
		{
			return false;
		}
		// [step, nTotal) sorted, [0, step) unsorted
		vector<int> vTemp = vInit;
		sort(vTemp.begin(), vTemp.begin() + step);
		if (vTemp != vRef)
		{
			return false;
		}
		cout << "Insertion Sort" << endl;
		sort(vTemp.begin(), vTemp.begin() + step + 1);
		Print(vTemp);
		return true;
	}

	bool IsHeap(void)
	{
		vector<int> vTemp = vInit;

		make_heap(vTemp.begin(), vTemp.end());

		int step = 0;
		for (; step < nTotal; ++step)
		{
			pop_heap(vTemp.begin(), vTemp.begin() + nTotal - step);
//			Print(vTemp);
			if (vTemp == vRef)
			{
				break;
			}
		}

		if (step >= nTotal - 1)
		{
			return false;
		}

		pop_heap(vTemp.begin(), vTemp.begin() + nTotal - step - 1);
		cout << "Heap Sort" << endl;
		Print(vTemp);
		return true;
	}


	int main(void)
	{
		vInit.clear();
		vRef.clear();
		int k;
		cin >> nTotal;
		for (int i = 0; i < nTotal; ++i)
		{
			cin >> k;
			vInit.push_back(k);
		}
		for (int i = 0; i < nTotal; ++i)
		{
			cin >> k;
			vRef.push_back(k);
		}

		if (IsInsertion2())
		{
			return 0;
		}

		if (IsHeap())
		{
			return 0;
		}
		return -1;
	}
}

// rename this to main int PAT
int A1098Func(void)
{
	return nsA1098A::main();
}


void A1098(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1098Func();
	cout << endl;
}

void A1098(void)
{
 	A1098("data\\A1098-1.txt"); // I 1 2 3 5 7 8 9 4 6 0
 	A1098("data\\A1098-2.txt"); // H 5 4 3 1 0 2 6 7 8 9
	A1098("data\\A1098-3.txt"); // I 1 2 3 8 7 5 9 4 6 0
	A1098("data\\A1098-4.txt"); // I 0 1 2 3 4 5 6 7 8 9
	A1098("data\\A1098-5.txt"); // H 7 6 5 4 0 3 2 1 8 9
	A1098("data\\A1098-6.txt"); // H 0 1 2 3 4 5 6 7 8 9
}
