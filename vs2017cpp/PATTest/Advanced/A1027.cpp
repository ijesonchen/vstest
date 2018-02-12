/*
1027. Colors in Mars (20)

cost: 21:00

sln1: ÷±Ω”º∆À„
	10min 14/20 pt1,2,5¥ÌŒÛ

People in Mars represent the colors in their computers in a similar way as the Earth people.
That is, a color is represented by a 6-digit number, where the first 2 digits are for Red, 
the middle 2 digits for Green, and the last 2 digits for Blue. 
The only difference is that they use radix 13 (0-9 and A-C) instead of 16. 
Now given a color in three decimal numbers (each between 0 and 168), 
you are supposed to output their Mars RGB values.

Input

Each input file contains one test case which occupies a line 
containing the three decimal color values.

Output

For each test case you should output the Mars RGB value in the following format: 
first output "#", then followed by a 6-digit number where 
all the English characters must be upper-cased. 
If a single color is only 1-digit long, you must print a "0" to the left.

Sample Input
15 43 71
Sample Output
#123456
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;


// rename this to main int PAT
int A1027Func(void)
{
	int color[3];
	for (int i = 0; i < 3; ++i)
	{
		cin >> color[i];
	}
	string str("#000000");
	for (int i = 0; i < 3; ++i)
	{
		auto c = color[i];
		str[i * 2 + 1] += c / 13;
		str[i * 2 + 2] += c % 13;
	}
	cout << str << endl;
	return 0;
}


void A1027(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1027Func();
	cout << endl;
}

void A1027(void)
{
	A1027("data\\A1027-1.txt"); // 
}

