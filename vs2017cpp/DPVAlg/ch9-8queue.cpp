#include "main.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
/*
在8X8格的国际象棋上摆放八个皇后，使其不能互相攻击，
即任意两个皇后都不能处于同一行、同一列或同一斜线上，共有多少种摆法（92）

8皇后放置属于排列组合类问题，采用递归算法。
*/


class QueueBoard
{
public:
	int Search(void)
	{
		Search(0);
		cout << "ANS: " << nCount << ", checked: " << nCheck << endl;
		return nCount;
	}
	
	void Search(int i)
	{
		if (i >= nBoardLength)
		{
			return;
		}
		for (int j = 0; j < nBoardLength; ++j)
		{
			pBoardQueuep[i] = j;
			if (!CheckValidLast(i))
			{
				continue;
			}
			if (i == nBoardLength - 1)
			{
				++nCount;
			}
 			Search(i + 1);
		}
	}

	bool CheckValidLast(int iLast)
	{
		++nCheck;
		auto length = iLast;
		auto jLast = pBoardQueuep[iLast];
		for (size_t i = 0; i < length; i++)
		{
			auto j = pBoardQueuep[i];
			if (j == jLast)
			{
				return false;
			}
			auto k = iLast - i;
			if (jLast > j && (k == jLast - j))
			{
				return false;
			}
			if (j > jLast && (k == j - jLast))
			{
				return false;
			}
		}
		return true;
	}
private:
	static const int nBoardLength = 8;
	int pBoardQueuep[nBoardLength] = { 0 };
	int nCount = 0;
	int nCheck = 0;
	bool bbb = true;

};


void EightQueue(void)
{
	QueueBoard q;
	q.Search();

}
