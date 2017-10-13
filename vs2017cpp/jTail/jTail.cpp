#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::tr2;
using namespace chrono;

void main(int argc, char** argv)
{
	auto tv = 1.0;
	auto firstRead = 400;
	if (argc < 2)
	{
		cout << "exe path [timevalue]" << endl;
		return;
	}
	auto fn = argv[1];
	if (argc == 3)
	{
		tv = atof(argv[2]);
	}
	auto durSleep = chrono::duration<float, ratio<1, 1>>(tv);
	cout << "durSleep " << durSleep.count() << endl;
	cout << "filename: " << fn << endl;
	fstream f(fn, ios::in);
	if (!f)
	{
		cout << "open failed: " << fn << endl;
		return;
	}
	auto size = sys::file_size(fn);
	auto pos = 0;
	if (size > firstRead)
	{
		pos = (int)size - firstRead;
	}
	string s;
	while (true)
	{
		size = sys::file_size(fn);;
		if (pos != size)
		{
			f.seekg(pos);
			pos = (int)size;
			while (getline(f, s))
			{
				cout << s << endl;
			}
			f.clear();
			cout << endl;
		}
		this_thread::sleep_for(durSleep);
	}
}