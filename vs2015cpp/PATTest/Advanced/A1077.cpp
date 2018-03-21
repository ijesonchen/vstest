/*
1077. Kuchiguse (20)
100 ms
65536 kB
16000 B



The Japanese language is notorious for its sentence ending particles. 
Personal preference of such particles can be considered as a reflection of the speaker's personality. 
Such a preference is called "Kuchiguse" and is often exaggerated artistically in Anime and Manga. 
For example, the artificial sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:

Itai nyan~ (It hurts, nyan~)
Ninjin wa iyada nyan~ (I hate carrots, nyan~)
Now given a few lines spoken by the same character, can you find her Kuchiguse?

Input Specification:

Each input file contains one test case. 
For each case, the first line is an integer N (2<=N<=100). 
Following are N file lines of 0~256 (inclusive) characters in length, 
each representing a character's spoken line.
The spoken lines are case sensitive.

Output Specification:

For each test case, print in one line the kuchiguse of the character,
i.e., the longest common suffix of all N lines. If there is no such suffix, write "nai".

Sample Input 1:
3
Itai nyan~
Ninjin wa iyadanyan~
uhhh nyan~
Sample Output 1:
nyan~
Sample Input 2:
3
Itai!
Ninjinnwaiyada T_T
T_T
Sample Output 2:
nai
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
18:50
最长公共后缀
100句，每句最长256字符
依次读取，每次求最长公共后缀。为0输出nai
19：16 pass
*/
namespace nsA1077A
{
	string suffix;

	void Check(const string& s)
	{
		size_t len1 = suffix.length();
		size_t len11 = len1;
		size_t len2 = s.length();
		size_t len = std::min(len1, len2);
		size_t i = 0;
		for (; i < len; ++i)
		{
			if (suffix[--len1] != s[--len2])
			{
				break;
			}
		}
		suffix.erase(0, len11 - i);
	}

	void main(void)
	{
		int n = 0;
		cin >> n;
		getline(cin, suffix);
		getline(cin, suffix);
		for (int i = 1; i < n && !suffix.empty(); ++i)
		{
			string s;
			getline(cin, s);
			Check(s);
		}
		if (!suffix.empty())
		{
			cout << suffix << endl;
		}
		else
		{
			cout << "nai" << endl;
		}
	}
}

// rename this to main int PAT
int A1077Func(void)
{
	nsA1077A::main();
	return 0;
}


void A1077(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1077Func();
	cout << endl;
}

void A1077(void)
{
	A1077("data\\A1077-1.txt"); // 
	A1077("data\\A1077-2.txt"); // 
}

