/*
1098. Insertion or Heap Sort (25)
100 ms
65536 kB

总结：
	1. 插入排序可能存在中间部分已排序的情况，需要跳过（搜索最长已排序长度最简单）
	2. 如果接近满分，但是短时间没有解决，应该暂缓，因为不确定最后的点要多久通过


20min 11/25, 20min 23/25, 15min 23/25。20MIN pass

15：50
判断插入排序/堆排序

1. 是否插入？否则为堆
仅判断插入（否则返回非0）
16：10 11/25 非01，3，5 异常2

判断Heap
16:30 23/25 wa2

只判断heap
16：33 12/25 非0 0,2,4

2应为insert
16：45 加入临界tc（3-6），未找到问题
测试：vRef确定未完成排序

14：30
改进： 利用sort模拟insert
14：40 23/25 wa2
使用A1089的insert判定算法可以通过PT0,2,4

问题：insertion当部分数据已排序时，会有跳过步骤
A1098::IsInsertion/IsInsertion2都是按照最早的步骤输出
A1089::IsInsertion则是按照最晚的步骤输出。

A1098::IsInsertion2
bug-fix-1：跳过当前已排序部分
14:50 PASS

如：
2 0 1 3 4 5 7 6 原始
0 2 1 3 4 5 7 6 参考1
0 1 2 3 4 5 7 6 参考2：题目给出的参考
0 1 2 3 4 5 6 7 参考3：题目需要的结果

参考2到参考3的步骤，中间会跳过排序好的3 4 5 7
A1089::IsIns: 先搜索前面排序部分(尽可能多），再比较尾部是否相等，则确定到位置7
A1098::IsIns: 先搜索后面相同部分(尽可能多），在比较前面是否排序，则确定到位置3
A1098::IsIns2:从位置1开始排序，直到和参考相等（尽可能早），此时在位置3
bug-fix-1：跳过可能相等的排序（尽可能晚），此时在位置7
如果确定位置3，下一步排序后，输出仍然是参考2
如果确定位置7，下一步排序后则输出参考3


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
				// bug-fix-1: 跳过当前已排序部分
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

