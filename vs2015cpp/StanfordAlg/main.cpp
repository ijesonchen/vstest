#include <windows.h> 
#include <stdio.h> 

#include "common.h"
#include <iostream>
#include <string>


void MulInteger(void); 
void CountInversions(void);
void QuickSortPartition(void);
void Contraction(void);
void SCC(void);
void DijkstraShortestPath(void);
void DijkstraShortestPath2(void);
void MedianHeap(void);
void TwoSum(void);
void Greedy(void);
// wk10 bitDiff可以将24bit转换为3个4bit, diff为256/2个可能，然后对每一个diff后求和。
// 需要测试是否能够加快速度。
void Clustering(void);
void DynamicProgramming(void);
void KnapSack(void);
// wk13: try Johnson alg, correct CLRS 25.3 pseudo code.
void AllPairShortestPath(void);
// wk14
void TravelingSalesmanProblem(void);
void ApproxTravelingSalesmanProblem(void);
void Test2Sat(void);
void TestClrs22(void);
using namespace std;


bool ctrlhandler(DWORD fdwctrltype)
{
	switch (fdwctrltype)
	{
		// handle the ctrl-c signal. 
	case CTRL_C_EVENT:
		printf("ctrl-c event\n\n");
		return(true);

		// ctrl-close: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		printf("ctrl-close event\n\n");
		return(true);

		// pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		printf("ctrl-break event\n\n");
		return false;

	case CTRL_LOGOFF_EVENT:
		printf("ctrl-logoff event\n\n");
		return false;

	case CTRL_SHUTDOWN_EVENT:
		printf("ctrl-shutdown event\n\n");
		return false;

	default:
		return false;
	}

	putchar('q');
}
void main(void)
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true))
	{
		printf("\nthe control handler is installed.\n");
		printf("\n -- now try pressing ctrl+c or ctrl+break, or");
		printf("\n try logging off or closing the console...\n");
		printf("\n(...waiting in a loop for events...)\n\n");

		char ch;
		cin >> ch;

		cout << "input " << ch << endl;
	}
	else
		printf("\nerror: could not set control handler");

	return;
	auto tp = chrono::high_resolution_clock::now();

	DijkstraShortestPath();

	TimeCost(tp);
	cout << "enter to exit." << endl;
	getchar();
}
