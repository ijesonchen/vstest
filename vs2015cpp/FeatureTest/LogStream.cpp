#include <sstream>
#include <iostream>

using namespace std;

class LogStreamInherit : public ostream, stringbuf
{
public:
	LogStreamInherit() : ostream(this)
	{ };
};

LogStreamInherit LogInh;

template<typename T>
LogStreamInherit& operator << (LogStreamInherit& l, const T& t)
{
	cout << t;
	return l;
}

class LogStreaming
{
public:
};


template<typename T>
LogStreaming& operator << (LogStreaming& l, const T& t)
{
	cout << t;
	return l;
}

inline LogStreaming& sendl(LogStreaming& l)
{
	cout << std::endl;
	return l;
}

LogStreaming Log;

void LogStreamTest(void)
{
	LogInh << "test " << "asdf " << 23 << std::endl;
	Log << "test " << "asdf " << 23 << sendl;
	// failed: l << endl
	// endl is a function like: ostream& endl(ostream& os);
	// howto ? not resolved.
	//		1. inherit LogStreaming from ostream and streambuf
	//		2. overload endl
}