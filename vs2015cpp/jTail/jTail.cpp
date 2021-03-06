#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::experimental;
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
	int maxRead = 1000;
	if (argc == 4)
	{
		maxRead = atoi(argv[3]);
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
	auto size = filesystem::file_size(fn);
	auto pos = 0;
	if (size > firstRead)
	{
		pos = (int)size - firstRead;
	}
	string s;
	while (true)
	{
		size = filesystem::file_size(fn);;
		if (pos != size)
		{
			if (pos + maxRead < size)
			{
				pos = int(size - maxRead);
			}
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