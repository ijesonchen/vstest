#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "repoString.dat"

//////////////////////////////////////////////////////////////////////////
/*
convert repo info by "svn info" to string def in cpp
used to build repo info into exec

example with vs2015, svn repo

PROPERTY SET:
	Project Property, Build Event, Pre-Build Event, Command Line, Edit
	
	with command line:
	svn info $(SolutionDir) > $(SolutionDir)Bin\repoInfo.tmp
	svn stat $(SolutionDir) > $(SolutionDir)Bin\repoStat.tmp
	$(SolutionDir)doc\SvnInfo2CppSrcStr.exe $(SolutionDir)Bin\repoInfo.tmp $(SolutionDir)Bin\repoStat.tmp $(SolutionDir)repoString.tmp
	
CODE:
	#include "repoString.tmp"

	stringstream ssRepo;
	ssRepo << u8"RepoInfo:" << "\r\n";
	for (auto p : g_u8RepoString)
	{
	ssRepo << "\r\n" << p;
	}

	Log(INFO, ssRepo.str());

	stringstream ssBuild;
	ssBuild << "\r\n\r\n----> Build: " << __DATE__ << ", " << __TIME__ << "\r\n";

	Log(INFO, ssBuild.str());
*/
//////////////////////////////////////////////////////////////////////////




using namespace std;



const int knArgc = 4;

struct Tag {
	string src;
	string dst;
	Tag(const string& s, const string& d) : src(s), dst(d) {}
};

vector<string> vReadInfo;
vector<Tag> vInfoTag = {
	{ "Last Changed Rev",		"Modify Rev "},
	{ "Last Changed Date",		"Modify Date"},
	{ "Revision",				"Top    Rev " },
	{ "Relative URL",			"Repo   Path"},
	{ "Working Copy Root Path", "Local  Path"},
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


	if (vWriteInfo.empty())
	{
		return false;
	}
	f << RawString("---->RepoInfo: ");
	for (auto& s : vWriteInfo)
	{
		f << RawString(s);
	}
	f << "\t\"\"," << endl;



	if (!vWriteStat.empty())
	{
		f << RawString("---->FileChangeList: ");
		for (auto& s : vWriteStat)
		{
			f << RawString(s);
		}
		f << "\t\"\"," << endl;
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
		cout << "exec info.txt status.txt src.cpp" << endl;
		return -100;
	}


	if (!ReadFile(argv[1], vReadInfo))
	{
		cout << "ReadFile failed: " << argv[1] << endl;
		return -1;
	}

	if (!ReadFile(argv[2], vReadStat))
	{
		cout << "ReadFile failed: " << argv[2] << endl;
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
		cout << "ParseFile failed: " << argv[1] << endl;
		return -3;
	}

	// no return check. maybe no change list
	ParseFile(vReadStat, vStatTag, vWriteStat);

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
		cout << "WriteSrc2 failed: " << argv[3] << endl;
		return -5;
	}
	
	cout << "SvnInfo2CppSrcStr done." << endl;

	return 0;
}