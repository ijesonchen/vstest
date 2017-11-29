/*
1006. Sign In and Sign Out (25)

At the beginning of every day, the first person who 
signs in the computer room will unlock the door, and 
the last one who signs out will lock the door. Given
the records of signing in's and out's, you are supposed 
to find the ones who have unlocked and locked the door 
on that day.

Input Specification:

Each input file contains one test case. Each case
contains the records for one day. The case starts 
with a positive integer M, which is the total number 
of records, followed by M lines, each in the format:

ID_number Sign_in_time Sign_out_time
where times are given in the format HH:MM:SS, and ID 
number is a string with no more than 15 characters.

Output Specification:

For each test case, output in one line the ID numbers 
of the persons who have unlocked and locked the door on 
that day. The two ID numbers must be separated by one space.

Note: It is guaranteed that the records are consistent. 
That is, the sign in time must be earlier than the sign 
out time for each person, and there are no two persons 
sign in or out at the same moment.

Sample Input:
3
CS301111 15:30:28 17:00:10
SC3021234 08:00:00 11:25:25
CS301133 21:45:00 21:58:40
Sample Output:
SC3021234 CS301133
*/

#include "patMain.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> name;
vector<string> si;
vector<string> so;


void A1006(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	int n = 0;
	cin >> n;
	string s1, s2, s3;
	for (int i = 0; i < n; ++i)
	{
		cin >> s1 >> s2 >> s3;
		name.push_back(s1);
		si.push_back(s2);
		so.push_back(s3);
	}

	auto simin = min_element(si.begin(), si.end());
	auto namemin = name[simin - si.begin()];
	auto somax = max_element(so.begin(), so.end());
	auto namemax = name[somax - so.begin()];
	cout << namemin << " " << namemax << endl;
}

void A1006(void)
{
	A1006("data\\A1006-1.TXT"); // SC3021234 CS301133
}