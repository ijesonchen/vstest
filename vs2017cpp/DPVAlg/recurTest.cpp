#include "main.h"
void RecurTest(void);

using namespace std;

// _ch个字符，_len个位。获取所有可能的组合（字符可重复）。参考：数字的位表示
class AllBit
{
public:
	AllBit(int _len, int _ch) :len(_len), data(_len), ch(_ch) {};

	void PrintAllBit(void)
	{
		Search(0);
	}

	void Search(int i)
	{
		if (i >= len)
		{
			cout << ++idx << ": ";
			for (auto d : data)
			{
				cout << char('a' + d) << " ";
			}
			cout << endl;
			return;
		}
		for (int j = 0; j < ch; ++j)
		{
			data[i] = j;
			Search(i + 1);
		}
	}
private:
	const char ch;
	const int len;
	int idx = 0;
	vector<char> data;
};

class CharPermutation
{
public:
	CharPermutation(int _len): len(_len) {};

	void PrintPerm(void)
	{
		string s;
		for (size_t i = 0; i < len; i++)
		{
			s.push_back('a' + char(i));
		}
		Perm(s, 0, (int)s.length());
		cout << "total permutaion: " << count << endl;
	}

private:
	void Perm(string& s, int start, int len)
	{
		if (len == 1)
		{
			++count;
			cout << s << endl;
			return;
		}
		for (auto i = start; i - start < len; ++i)
		{
			swap(s[start], s[i]);
			Perm(s, start + 1, len - 1);
			swap(s[start], s[i]);
		}
	}
	const int len;
	int count = 0;
};


void RecurTest(void)
{
	CharPermutation cp(1000);
	cp.PrintPerm();
	return;
	AllBit ab(3, 3);
	ab.PrintAllBit();
}