#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

bool IsVadReExp(const std::string& pattern)
{
	try
	{
		regex re(pattern);
	}
	catch (exception& e)
	{
		cout << "\t" << e.what() << endl;
		return false;
	}
	return true;
}

char IsVadUserReChar(const char c)
{
	switch (c)
	{
	case '&':
	case '|':
	case '!':
		return 0;
	default:
		return c;
		break;
	}
	return c;
}

bool IsVadReExpUser(std::string pattern)
{
	auto fr = pattern.front();
	if (fr != '!' && !IsVadUserReChar(fr))
	{
		return false;
	}
	if (!IsVadUserReChar(pattern.back()))
	{
		return false;
	}
	auto length = pattern.length();
	if (length < 3)
	{
		return false;
	}
	auto last = IsVadUserReChar(pattern[0]);
	for (size_t i = 1; i < length; i++)
	{
		auto current = IsVadUserReChar(pattern[i]);
		if (current == last)
		{
			return false;
		}
		last = current;
	}
	return true;
}

void ReExpTest(void)
{
	vector<string> res =
	{
		"a&b|c",
		"!a&b|c",
		"&a&b|c",
		"a&b|c|",
		"a&b|c||",
		"a&b|c&&|&",
		"a&(b|c)",
		"a&(b|c))",
		"a&(b|c)**",
		"a&(b|c))**",
		"a&(b|c)^",
		"a&(b|c))^",
		"***@@#$%^%*(!%)&#",
		u8"你好&最近|怎么样",
		u8"!你好&最近|怎么样",
		u8"&你好&最近|怎么样",
		u8"你好&最近|怎么样!",
		u8"你好&最近|怎么样&",
		u8"你好&最近|怎么样&!&",
		u8"!&你好&最近|怎么样",
	};

	for (const auto& p : res)
	{
		if (!IsVadReExp(p))
		{
			cout << "x      " << p << endl;
		}
		else if (!IsVadReExpUser(p))
		{
			cout << "   x    " << p << endl;
		}
		else
		{
			cout << "      v " << p << endl;
		}
	}
	
}