/*
1011. World Cup Betting (20)
cost: 16:50 30min

总结：有时候，浮点数会有精度舍入问题，一般float换double不一样能解决
	可以考虑手工调整（先多保留1位精度，判断倒数第二位 >=5，则增加 0.1的精度）
	由于题目往简单方面考虑，可以不考虑调整。
		可能是编译器不同导致的精度处理问题。实测不调整也可以AC
	

With the 2010 FIFA World Cup running, football fans the world 
over were becoming increasingly excited as the best players 
from the best teams doing battles for the World Cup trophy in 
South Africa. Similarly, football betting fans were putting 
their money where their mouths were, by laying all manner of 
World Cup bets.

Chinese Football Lottery provided a "Triple Winning" game. The 
rule of winning was simple: first select any three of the games. 
Then for each selected game, bet on one of the three possible 
results -- namely W for win, T for tie, and L for lose. There 
was an odd assigned to each result. The winner's odd would be 
the product of the three odds times 65%.

For example, 3 games' odds are given as the following:

W    T    L
1.1  2.5  1.7
1.2  3.0  1.6
4.1  1.2  1.1
To obtain the maximum profit, one must buy W for the 3rd game, 
T for the 2nd game, and T for the 1st game. If each bet takes 2
yuans, then the maximum profit would be 
(4.1*3.0*2.5*65%-1)*2 = 37.98 yuans (accurate up to 2 decimal places).

Input

Each input file contains one test case. Each case contains the 
betting information of 3 games. Each game occupies a line with 
three distinct odds corresponding to W, T and L.

Output

For each test case, print in one line the best bet of each game,
and the maximum profit accurate up to 2 decimal places. The 
characters and the number must be separated by one space.

Sample Input
1.1 2.5 1.7
1.2 3.0 1.6
4.1 1.2 1.1
Sample Output
T T W 37.98
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// rename this to main int PAT
int A1011Func(void)
{
	float f1, f2, f3;
	float res = 1;
	int loop = 3;
	
	for (int i = 0; i < loop; ++i)
	{
		cin >> f1 >> f2 >> f3;
		float t = max(max(f1, f2), f3);
		if (t == f1) cout << "W ";
		else if (t == f2) cout << "T ";
		else if (t == f3) cout << "L ";
		else throw 0;
		res *= t;
	}
	res = (res * 0.65f - 1)*2;
	// 针对题目示例
	// 调整精度：37.975 float是37.97499999..,所以输出37.97.double一样
	// 实际上不调整也可以AC
	char buf[1000];
	sprintf(buf, "%.3lf", res);
	string s = buf;
	if (s[s.length() - 2] >= '5')
	{
		res += .001f;
	} 
	printf("%.2f", res);
	return 0;
}


void A1011(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1011Func();
	cout << endl;
}

void A1011(void)
{
	A1011("data\\A1011-1.txt"); // 37.98
}

