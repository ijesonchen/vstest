#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <sstream>
#include "common.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////
//
// see "Note for STL thread support library" (note-stl-thread.md) on gitpages
//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// test for thread parameter & return value (with promise & future)

struct ThreadParam
{
	int x = 0;
	int y = 0;
};

struct ThreadResult
{
	int x = 0;
	int y = 0;
};

std::string ThreadString(void)
{
	auto id = this_thread::get_id();
	stringstream ss; 
	ss << "Thread " << id << ": ";

	return ss.str();
}

void ThreadFunc(ThreadParam thParam, promise<ThreadResult> proRes)
{
	this_thread::yield();

	auto id = this_thread::get_id();
	chrono::seconds sleepSec(2);

	cout << "**Thread " << id << ": Starts, x: " << thParam.x << ", y: " << thParam.y << endl;

	
	cout << "**sleep before setvalue" << endl;
	this_thread::sleep_for(sleepSec);

	ThreadResult res;
	res.x = thParam.x * 10;
	res.y = thParam.y * 10;
	proRes.set_value(res);
	
	cout << "**sleep before exit" << endl;
	this_thread::sleep_for(sleepSec);
}

void PromiseFutureTest()
{
	/*
>>thread prep
>>thread start
**Thread 11780: Starts, x: 10, y: 20
**sleep before setvalue
**sleep before exit
>>futResult ready
>>result 100 200
>>thread join
	*/
	ThreadParam thParam;
	thParam.x = 10;
	thParam.y = 20;
	promise<ThreadResult> proResult;
	auto futResult = proResult.get_future();
	cout << ">>thread prep " << endl;
	thread th(ThreadFunc, thParam, std::move(proResult));
	cout << ">>thread start " << endl;

	futResult.wait();
	cout << ">>futResult ready" << endl;


	auto thRes = futResult.get();

	cout << ">>result " << thRes.x << " " << thRes.y << endl;

	th.join();
	cout << ">>thread join" << endl;
}

//////////////////////////////////////////////////////////////////////////
// yield test
/*
if cpu is busy, yield will wait till next cpu time slice
if cpu is spare, yield will use all cpu time.
*/



volatile bool bRunning = true;

void ThreadYield(void)
{
	auto ts = ThreadString();
	auto s = ts + "start...\n";
	cout << s;

	if (!BindCpu(1))
	{
		s = ts + "bind cpu  failed.\n";
		cout << s;
	}

	auto tp1 = chrono::high_resolution_clock::now();
	chrono::seconds sec(1);
	int n = 0;

	while (bRunning)
	{
//		this_thread::yield(); // release cpu, so that other thread can use it.
		++n;
		auto tp2 = chrono::high_resolution_clock::now();
		if (tp2 - tp1 > sec)
		{
			cout << n << endl;
			n = 0;
			tp1 = tp2;
		}
	}

	s = ts + "exit...\n";
	cout << s;
}

void YieldTest()
{
	thread th(ThreadYield);

	this_thread::sleep_for(chrono::seconds(20));
	bRunning = false;
	cout << ">> false\n";

	th.join();
}

//////////////////////////////////////////////////////////////////////////
// exception test
// If the function throws an exception, std::terminate is called. 

void ThredException(void)
{
	auto ts = ThreadString();
	auto s = ts + "start...\n";
	cout << s;

	throw exception("thread exception test.");

	s = ts + "exit.\n";
	cout << s;
}

void ThreadExceptionTest()
{
	try
	{
		throw exception("main exception test.");
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		thread th(ThredException);
		th.join();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

void ThreadPassByRef(const vector<int>& pv)
{
	cout << this_thread::get_id() << ": " << &pv << endl;
	this_thread::sleep_for(chrono::seconds(10));
}

void TestPassByRef(void)
{
	vector<int> v(20*1024 * 1024, 0);
	auto length = 10;
	vector<thread> vt;
	for (size_t i = 0; i < length; i++)
	{
		vt.emplace_back(ThreadPassByRef, std::ref(v));
	}

	for (auto& i : vt)
	{
		i.join();
	}
}

void ThreadTest(void)
{
	TestPassByRef();
	return;
	PromiseFutureTest();
	YieldTest();
	ThreadExceptionTest();
}