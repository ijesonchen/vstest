#include <locale>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <windows.h>

void LocaleTest(void);
//////////////////////////////////////////////////////////////////////////

/*
win10 , vs2017 15.3 locale works with : chs, .936, zh-CN, chinese-simplified, CHN, CHS, but not china
Language Strings
https://msdn.microsoft.com/en-us/library/39cwe7zf.aspx
Country/Region Strings
https://msdn.microsoft.com/en-us/library/cdax410z.aspx

*/

using namespace std;

void SetLocaleAndIsDigit()
{
	setlocale(LC_ALL, "C");
	cout << "*中文测试*" << endl;

	string id = "你好";
	id = id.substr(0, find_if(id.begin(), id.end(), [](char ch) { return std::isdigit(ch, locale("chs")); }) - id.begin());
}

/*
1. cout locale test：IDE/操作系统版本，setlocale设置，cout能否正常输出中文。
*与编译系统无关。vs15 chs, win10下编译，win10正常，08R2异常。
** win10 / 08R2 不调用setlocale，直接cout中文可以正常显示。

| vs/os        | locale  | cout |
| ------------ | ------- | ---- |
| 15/17, WIN10 | C / chs | V    |
| 15, 08R2     | C       | V    |
| 15, 08R2     | chs     | X    |

2. isdigit直接处理ansi中文字符会有问题。可以考虑使用std::isdigit(char, std::local&)。
find_if中的判别式使用lambda表达式处理:  [](const char ch){ return std::isdigit(ch, std::local("chs")); }

3. mbstowcs/wcstombs是locale相关。中文下"chs"才能正确转换。

4. ansi到Unicode转换建议使用平台相关函数。
	windows建议使用WideCharToMultiByte，可以自动获取系统字符集设置
	linux建议使用iconv
	其他方案：
		mbstowcs/wcstombs全局locale相关， mbstowcs_l可以指定locale但似乎是微软的扩展
		wstring_convert是C++11标准，但是问题：a)速度相对较慢
											b)需要用到codecvt头文件，gcc 5.2开始支持，需要clang
    ** gcc 5.2 开始支持codecvt
*/


std::wstring DecAnsi(const std::string& strAnsi)
{
	const char* pAnsi = strAnsi.c_str();
	size_t len = mbstowcs(nullptr, pAnsi, 0) + 1; // should work with locale "chs"
	if (len == (size_t)-1)
	{
		return L"";
	}
	wchar_t* wp = new wchar_t[len];
	std::unique_ptr<wchar_t> wup(wp);
	wp[0] = 0;
	wp[len - 1] = 0;

	len = mbstowcs(wp, pAnsi, len);
	if (len == (size_t)-1)
	{
		return L"";
	}
	return wp;
}



std::string EncAnsiWin(const std::wstring& strUnicode)
{
	const wchar_t* pUnicode = strUnicode.c_str();
	auto len = WideCharToMultiByte(CP_ACP, 0, pUnicode, (int)strUnicode.length(), nullptr, 0, nullptr, nullptr);
	if (!len)
	{
		return "";
	}
	char* ap = new char[len + 1];
	std::unique_ptr<char> aup(ap);
	ap[0] = 0;
	ap[len - 1] = 0;
	ap[len] = 0;


	len = WideCharToMultiByte(CP_ACP, 0, pUnicode, (int)strUnicode.length(), ap, len, nullptr, nullptr);

	if (len == (size_t)-1)
	{
		return "";
	}
	return ap;
}


std::wstring DecAnsiWin(const std::string& strAnsi)
{
	const char* pAnsi = strAnsi.c_str();
	auto len = MultiByteToWideChar(CP_ACP, 0, pAnsi, (int)strAnsi.length(), nullptr, 0);

	if (!len)
	{
		return L"";
	}
	wchar_t* wp = new wchar_t[len + 1];
	std::unique_ptr<wchar_t> wup(wp);
	wp[0] = 0;
	wp[len - 1] = 0;
	wp[len] = 0;

	len = MultiByteToWideChar(CP_ACP, 0, pAnsi, (int)strAnsi.length(), wp, len);

	if (!len)
	{
		return L"";
	}
	return wp;
}



void ClibConvTest()
{
	setlocale(LC_ALL, "C"); // wrong
//	setlocale(LC_ALL, "chs"); // right
	string s = "你好test你好";
	auto w = DecAnsi(s);
}

void Win32ConvTest()
{
	string s = "你好test你好";
	cout << 1 << s << endl;
	auto w = DecAnsiWin(s);
	wcout.imbue(locale(""));
	wcout << 2 << w << endl;
	auto ss = EncAnsiWin(w);
	cout << 3 << ss << endl;
}

void GetLocaleInfo(void)
{
	std::wcout << "User-preferred locale setting is " << std::locale("").name().c_str() << '\n';
	// on startup, the global locale is the "C" locale
	std::wcout << 1000.01 << '\n';
	// replace the C++ global locale as well as the C locale with the user-preferred locale
	std::locale::global(std::locale(""));
	// use the new global locale for future wide character output
	std::wcout.imbue(std::locale());
	// output the same number again
	std::wcout << 1000.01 << '\n';
}

void LocaleTest(void)
{
	GetLocaleInfo();
	SetLocaleAndIsDigit();
	ClibConvTest();
	Win32ConvTest();
}
