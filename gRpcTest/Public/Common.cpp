#include "common.h"

#pragma warning(disable: 4996)

using namespace std;

std::string Timet2String(time_t tm)
{
	auto tmStru = localtime(&tm);
	const auto bufLen = 80;
	char buffer[bufLen];
	strftime(buffer, bufLen, "%Y-%m-%d %H:%M:%S", tmStru);
	buffer[bufLen - 1] = 0;
	return buffer;
}