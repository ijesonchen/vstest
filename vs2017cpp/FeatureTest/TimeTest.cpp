#include <chrono>
#include <iostream>
#include <windows.h>

/*
NOT THREAD-SAFE:
gmtime: tm *gmtime( const time_t *time )
localtime: tm *localtime( const time_t *time )
ctime: char* ctime( const time_t* time )
asctime: char* asctime( const std::tm* time_ptr )

THREAD-SAFE:
mktime: time_t mktime( std::tm* time )
strftime: size_t strftime( char* str, size_t count,
				 const char * format, const struct tm * time );

<iomanip>
std::put_time: template< class CharT > 
			put_time(const std::tm* tmb, const CharT* fmt);
std::get_time: template< class CharT >
			get_time( std::tm* tmb, const CharT* fmt )

*/

#include <ctime>

using namespace std;

void TimeTest(void)
{
	auto now = chrono::system_clock::now();
	auto tNow = chrono::system_clock::to_time_t(now);

	TIME_ZONE_INFORMATION   tzi;
	memset(&tzi, 0, sizeof(tzi));
	GetSystemTime(&tzi.StandardDate);
	GetTimeZoneInformation(&tzi);

	DYNAMIC_TIME_ZONE_INFORMATION dzi;
	memset(&dzi, 0, sizeof(dzi));
	GetDynamicTimeZoneInformation(&dzi);

	time_t t = 0;
	tm tm1, tm2;
	gmtime_s(&tm1, &t);
	localtime_s(&tm2, &t);

	long ntz = 0;
	_get_timezone(&ntz);
	auto ttt = time(nullptr);
	
}