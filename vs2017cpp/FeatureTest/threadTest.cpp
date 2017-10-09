#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <sstream>
#include "common.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////
/*
1. return value of thread function is ignored.
2. throw exception in thread function will call std::terminate.
3. use standard thread promise & future to return value and exception for caller
4. yield will release cpu so other thread can use it. 


*/
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// test for thread parameter & return velue (with promise & future)

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

NY: thread no yield
WY: thread with yield

| cond      | NY%  | WY%  | DETAIL          |
| --------- | ---- | ---- | --------------- |
| NY*1      | 100% |      |                 |
| WY*1      |      | 100% |                 |
| 1 NY, 1WY | 100% | 0%   |                 |
| 2 NY, 2WY | 100% | 0%   | 50% per NY      |
| (2-4)NY   | 100% |      | Load balanced   |
| (2-4)WY   |      | 100% | Load unbalanced |

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
// Any return value from the function is ignored. 
// If the function throws an exception, std::terminate is called. 
// In order to pass return values or exceptions back to the calling thread, 
// std::promise or std::async may be used.

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

void ThreadTest(void)
{
	PromiseFutureTest();
	YieldTest();
	ThreadExceptionTest();
}