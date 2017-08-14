#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "repoString.dat"

using namespace std;

const int knArgc = 4;

struct Tag {
	string src;
	string dst;
	Tag(const string& s, const string& d) : src(s), dst(d) {}
};

vector<string> vReadInfo;
vector<Tag> vInfoTag = {
	{ "Last Changed Rev", "Modify Rev"},
	{ "Last Changed Date", "Modify Date"},
	{ "Revision", "Top Rev" },
	{ "Relative URL", "Repo Path"},
	{ "Working Copy Root Path", "Local Path"},
};
vector<string> vReadStat;
vector<Tag> vStatTag = {
	{ "M       ", "*) " },
	{ "?       ", "+) " },
};

vector<string> vWriteInfo;
vector<string> vWriteStat;

bool ReadFile(const std::string fn, vector<string>& v)
{
	fstream f(fn, ios::in);
	if (!f)
	{
		return false;
	}
	string s;
	while (getline(f, s))
	{
		v.push_back(s);
	}
	return v.size() ? true : false;
}

bool ParseFile(vector<string>& src, vector<Tag>& tag, vector<string>& vWrite)
{
	auto ret = false;
	for (auto& t : tag)
	{
		for (auto& s : src)
		{
			if (s.find(t.src) != string::npos)
			{
				ret = true;

				vWrite.push_back(s.replace(0, t.src.length(), t.dst));
			}
		}
	}
	return ret;
}

string RawString(const string& s)
{
	stringstream ss;
	ss << "\tR\"###(" << s << ")###\"" << "," << endl;
	auto st = ss.str();
	return ss.str();
}


bool WriteSrc2(const std::string fn)
{
	fstream f(fn, ios::out);
	if (!f)
	{
		return false;
	}
	f << u8R"~~~(const char* g_u8RepoString[] = {)~~~";
	f << endl;


	if (!vWriteInfo.empty())
	{
		f << RawString("---->RepoInfo: ");
		for (auto& s : vWriteInfo)
		{
			f << RawString(s);
		}
		f << "\t\"\"" << endl;
	}



	if (!vWriteStat.empty())
	{
		f << RawString("---->FileChangeList: ");
		for (auto& s : vWriteStat)
		{
			f << RawString(s);
		}
	}

	f << u8R"~~~(};)~~~";
	
	f << endl;


	return true;
}

bool WriteSrc(const std::string fn)
{
	fstream f(fn, ios::out);
	if (!f)
	{
		return false;
	}
	string s = u8R"~~~(asdfasfd)~~~";
	f << u8R"~~~(    const char* g_u8RepoString = u8R"###()~~~" << endl;

	if (!vWriteInfo.empty())
	{
		f << "---->RepoInfo: " << endl;
		for (auto& s : vWriteInfo)
		{
			f << s << endl;
		}
		f << endl;
	}


	if (!vWriteStat.empty())
	{
		f << "---->FileChangeList: " << endl;
		for (auto& s : vWriteStat)
		{
			f << s << endl;
		}
		f << u8R"~~~()###";)~~~" << endl << endl;
	}

	return true;
}

int main(int argc, char** argv)
{	
	if (argc != knArgc)
	{
		cout << "exec info.txt status.txt src.cpp";
		return -1;
	}


	if (!ReadFile(argv[1], vReadInfo))
	{
		return -1;
	}

	if (!ReadFile(argv[2], vReadStat))
	{
		return -2;
	}

	// "Last Changed Date: 2017-08-11 16:11:08 +0800".length = 44
	for (auto& s : vReadInfo)
	{
		if (s.find("Last Changed Date") != string::npos)
		{
			s = s.substr(0, 44);
			break;
		}
	}

	if (!ParseFile(vReadInfo, vInfoTag, vWriteInfo))
	{
		return -3;
	}

	if (!ParseFile(vReadStat, vStatTag, vWriteStat))
	{
		return -4;
	}

	for (auto& s : vWriteInfo)
	{
		cout << s << endl;
	}

	if (!vWriteStat.empty())
	{
		cout << "FileChangeList: " << endl;
		for (auto& s : vWriteStat)
		{
			cout << s << endl;
		}
	}
	
	if (!WriteSrc2(argv[3]))
	{
		return -5;
	}
	
	cout << "done" << endl;

	return 0;
}