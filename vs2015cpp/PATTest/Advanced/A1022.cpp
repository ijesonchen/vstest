/*
1022. Digital Library (30)

cost: 15:20 40min

sln: 使用map做查询(map也不会超时）
	注意数据读取：cin >> var,之后使用getlin(cin, s)可能获取到当前的空行。

A Digital Library contains millions of books, 
stored according to their titles, authors, key words of their abstracts, publishers, and published years. 
Each book is assigned an unique 7-digit number as its ID. 
Given any query from a reader, you are supposed to output the resulting books, 
sorted in increasing order of their ID's.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer 
N (<=10000) which is the total number of books. 
Then N blocks follow, each contains the information of a book in 6 lines:

Line #1: the 7-digit ID number;
Line #2: the book title -- a string of no more than 80 characters;
Line #3: the author -- a string of no more than 80 characters;
Line #4: the key words -- each word is a string of no more than 10 characters without any white space, 
		and the keywords are separated by exactly one space;
Line #5: the publisher -- a string of no more than 80 characters;
Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].

It is assumed that each book belongs to one author only, 
and contains no more than 5 key words; 
there are no more than 1000 distinct key words in total; 
and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer 
M (<=1000) which is the number of user's search queries. 
Then M lines follow, each in one of the formats shown below:

1: a book title
2: name of an author
3: a key word
4: name of a publisher
5: a 4-digit number representing the year
Output Specification:

For each query, first print the original query in a line, 
then output the resulting book ID's in increasing order, each occupying a line. 
If no book is found, print "Not Found" instead.

Sample Input:
3
1111111
The Testing Book
Yue Chen
test code debug sort keywords
ZUCS Print
2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4: ZUCS Print
5: 2011
3: blablabla
Sample Output:
1: The Testing Book
1111111
2222222
2: Yue Chen
1111111
3333333
3: keywords
1111111
2222222
3333333
4: ZUCS Print
1111111
5: 2011
1111111
2222222
3: blablabla
Not Found
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;

struct A1022Book 
{
	string id;
	string title;
	string author;
	vector<string> kwds;
	string pub;
	string year;
};

bool A1022BookLess(const A1022Book* p1, const A1022Book* p2)
{
	return p1->id < p2->id;
}

A1022Book A1022ReadABook(void)
{
	A1022Book book;
	string kwd;
	getline(cin, book.id);
	getline(cin, book.title);
	getline(cin, book.author);
	getline(cin, kwd);
	getline(cin, book.pub);
	getline(cin, book.year);
	stringstream ss(kwd);
	string tmp;
	while (ss >> tmp)
	{
		book.kwds.push_back(tmp);
	}
	return book;
}

void A1022MapBooks(const vector<A1022Book*>& vpbook, int tag, unordered_map<string, vector<A1022Book*>>& mapKey)
{
	for (auto p : vpbook)
	{
		switch (tag)
		{
		case 0:
			mapKey[p->title].push_back(p);
			break;
		case 1:
			mapKey[p->author].push_back(p);
			break;
		case 2:
			for (auto& kwd: p->kwds)
			{
				mapKey[kwd].push_back(p);
			}
			break;
		case 3: 
			mapKey[p->pub].push_back(p);
			break;
		case 4:
			mapKey[p->year].push_back(p);
			break;
		default:
			throw 0;
			break;
		}
	}
}

// rename this to main int PAT
int A1022Func(void)
{
	const int maxTag = 5;
	int n, m;
	string strtmp;
	cin >> n;
	getline(cin, strtmp);
	vector<A1022Book> vbook;
	for (int i = 0; i < n; ++i)
	{
		vbook.push_back(A1022ReadABook());
	}

	vector<A1022Book*> vpbook;
	for (auto& b : vbook)
	{
		vpbook.push_back(&b);
	}
	sort(vpbook.begin(), vpbook.end(), A1022BookLess);

	unordered_map<string, vector<A1022Book*>> mkey[maxTag];
	for (int i = 0; i < maxTag; ++i)
	{
		A1022MapBooks(vpbook, i, mkey[i]);
	}

	cin >> m;
	getline(cin, strtmp);
	string query;
	string key;
	for (int i = 0; i < m; ++i)
	{
		getline(cin, query);
		cout << query << endl;

		int tag = query[0] - '0' - 1;
		key = query.substr(3);
		auto& vResult = mkey[tag][key];
		if (vResult.empty())
		{
			cout << "Not Found" << endl;
			continue;
		}
		for (auto p : vResult)
		{
			cout << p->id << endl;
		}
	}

	return 0;
}


void A1022(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1022Func();
	cout << endl;
}

void A1022(void)
{
	A1022("data\\A1022-1.txt"); // 
}

