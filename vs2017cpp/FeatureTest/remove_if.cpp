/*
对容器迭代器remove_if后需要对容器进行earse
*/


#include <iostream>  
#include <vector>
#include <algorithm> 

bool IsOdd(int i) { return ((i % 2) == 1); }

using namespace std;

void TestRemoveIf(void)
{
	vector<int> v = { 1,2,3,4,5,6,7,8,9 };            // 1 2 3 4 5 6 7 8 9

	auto end  = std::remove_if(v.begin(), v.end(), IsOdd);   // 2 4 6 8 ? ? ? ? ?
										
	for (auto p = v.begin(); p != end; ++p)
	{
		cout << *p << " "; // 2 4 6 8 
	}
	cout << endl;

	for (auto i : v)
	{
		cout << i << " "; // 2 4 6 8 5 6 7 8 9
	}
	cout << endl;
	
	v.erase(end, v.end());
	for (auto i : v)
	{
		cout << i << " "; // 2 4 6 8 
	}
	cout << endl;
}