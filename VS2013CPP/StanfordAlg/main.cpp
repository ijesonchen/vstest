#include <iostream>
#include <string>


void MulInteger(void); 
void CountInversions(void);
void QuickSortPartition(void);
void Contraction(void);
void SCC(void);
void DijkstraShortestPath(void);
void MedianHeap(void);
void TwoSum(void);
void Greedy(void);
// wk10 bitDiff可以将24bit转换为3个4bit, diff为256/2个可能，然后对每一个diff后求和。
// 需要测试是否能够加快速度。
void Clustering(void);
void DynamicProgramming(void);

using namespace std;

void main(void)
{
	DynamicProgramming();

	cout << "enter to exit." << endl;
	getchar();
}
