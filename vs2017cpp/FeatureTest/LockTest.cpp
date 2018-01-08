#include <mutex>
#include <shared_mutex>
#include <thread>

#include <iostream>
#include <cstdint>
#include <string>
#include <chrono>

void LockTest(void);
//////////////////////////////////////////////////////////////////////////
/*
see "Note for STL thread support library" (note-stl-thread.md) on gitpages
*/

using namespace std;

// mutex & variables
mutex mtx;
timed_mutex mtxTm;
recursive_mutex mtxRecur;
recursive_timed_mutex mtxRecurTm;
shared_mutex mtxShare;
shared_timed_mutex mtxShareTm;

int value = 0;

void Lock(void)
{
	unique_lock<timed_mutex> lock2(mtxTm, defer_lock);

	lock(mtx, mtxTm);

	lock_guard<mutex> lock1(mtx, adopt_lock);

}

void Guard(void)
{
	lock_guard<mutex> lock(mtx);
	++value;
	cout << this_thread::get_id() << ": " << value << endl;
}

void Scoped(void)
{
	// compile error, but scoped_lock realized in vs2017 15.3 
	// https://blogs.msdn.microsoft.com/vcblog/2017/08/11/c17-features-and-stl-fixes-in-vs-2017-15-3/
// 	std::scoped_lock lock(mtx1, mtx2, mtx3);
// 	++i1;
// 	cout << this_thread::get_id() << ": " << i1 << endl;
}




// RW lock with shared lock
class ThreadSafeCounter
{
public:
	std::uint64_t Get(void) const
	{
		std::shared_lock<std::shared_mutex> lock(mtx);
		return value;
	}

	std::uint64_t Inc(void)
	{
		std::unique_lock<std::shared_mutex> lock(mtx);
		return ++value;
	}

private:
	mutable std::shared_mutex mtx;
	std::uint64_t value = 0;
};



void TestRWLock()
{
	ThreadSafeCounter c;
	auto n = c.Get();
	c.Inc();
	n = c.Get();
	c.Inc();
	n = c.Get();
}

//////////////////////////////////////////////////////////////////////////
// call once
std::once_flag flag1;

void OnceTest()
{
	std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
	std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
	std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
}

//////////////////////////////////////////////////////////////////////////
// condition_variable
std::mutex m;
std::condition_variable cv;
std::string cvData;
bool ready = false;
bool processed = false;

void WorkerThread(void)
{
	// Wait until main() sends data
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, [] {return ready; });


	// after the wait, we own the lock.
	std::cout << "<<-- Worker thread is processing data and sleep 2 seconds.\n";
	cvData += " after processing";
	this_thread::sleep_for(chrono::seconds(2));


	// Send data back to main()
	processed = true;
	std::cout << "<<-- Worker thread signals data processing completed\n";

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lk.unlock();
	cv.notify_one();
}

void CVTest(void)
{

	std::thread worker(WorkerThread);

	cvData = "Example data";
	// send data to the worker thread
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		std::cout << "-->> main() data = " << cvData << '\n';
		std::cout << "-->> main() signals data ready for processing\n";
	}

	{
		std::lock_guard<std::mutex> lk(m);
		cv.notify_one();
		std::cout << "-->> main() notify_one but hold lock, sleep 2 seconds" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		std::cout << "-->> main() release lock" << endl;
	}

	// wait for the worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [] {return processed; });
	}
	std::cout << "-->> Back in main(), data = " << cvData << '\n';

	worker.join();

	/*
	-->> main() data = Example data
	-->> main() signals data ready for processing
	<<-- Worker thread is processing data and sleep 2 seconds.
	<<-- Worker thread signals data processing completed
	-->> Back in main(), data = Example data after processing
	*/
}



void WorkerThreadNoPred(void)
{
	// Wait until main() sends data
	std::cout << "<<-- Worker thread try lock...\n";
	std::unique_lock<std::mutex> lk(m);
	std::cout << "<<-- Worker thread try wait...\n";
	cv.wait(lk);


	// after the wait, we own the lock.
	std::cout << "<<-- Worker thread is processing data and sleep 2 seconds, then unlock.\n";
	cvData += " after processing";
	this_thread::sleep_for(chrono::seconds(2));

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	std::cout << "<<-- Worker thread unlock.\n";
	lk.unlock();

	std::cout << "<<-- Worker thread sleep 2 seconds before notify_one\n";
	this_thread::sleep_for(chrono::seconds(2));
	std::cout << "<<-- Worker thread notify_one\n";
	cv.notify_one();

	std::cout << "<<-- Worker thread sleep 2 seconds before exit\n";
	this_thread::sleep_for(chrono::seconds(2));
	std::cout << "<<-- Worker thread exited.\n";
}

void CVTestNoPred(void)
{

	std::thread worker(WorkerThreadNoPred);

	cvData = "Example data";
	// send data to the worker thread
	std::cout << "-->> main() data = " << cvData << '\n';
	std::cout << "-->> main() sleep 2 seconds" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	std::cout << "-->> main() notify_one" << endl;
	cv.notify_one();


	// wait for the worker
	std::cout << "-->> main() try lock...\n";
	std::unique_lock<std::mutex> lk(m);
	std::cout << "-->> main() try wait...\n";
	cv.wait(lk);
	std::cout << "-->> Back in main(), data = " << cvData << '\n';

	std::cout << "-->> main() wait worker thread to exit.\n";
	worker.join();
	std::cout << "-->> main() exit.\n";

	/*
	// 理论结果 空行表示sleep，无空行部分可以认为是同时运行
				<<-- Worker thread try lock...
				<<-- Worker thread try wait...
-->> main() data = Example data
-->> main() sleep 2 seconds

-->> main() notify_one
				<<-- Worker thread is processing data and sleep 2 seconds, thren unlock.
-->> main(), try lock...


				<<-- Worker thread unlock.
-->> main(), try wait...
				<<-- Worker thread sleep 2 seconds before notify_one

				<<-- Worker thread notify_one
-->> Back in main(), data = Example data after processing
-->> main(), wait worker thread to exit.
				<<-- Worker thread sleep 2 seconds before exit

				<<-- Worker thread exited.
-->> main() exit.
	// 实际结果，与理论顺序基本一致
				<<-- Worker thread try lock...
-->> main() data = Example data
				<<-- Worker thread try wait...
-->> main() sleep 2 seconds

-->> main() notify_one
-->> main() try lock...
				<<-- Worker thread is processing data and sleep 2 seconds, thren unlock.


				<<-- Worker thread unlock.
				<<-- Worker thread sleep 2 seconds before notify_one
-->> main() try wait...

				<<-- Worker thread notify_one
				<<-- Worker thread sleep 2 seconds before exit
-->> Back in main(), data = Example data after processing
-->> main() wait worker thread to exit.

				<<-- Worker thread exited.
-->> main() exit.
	*/
}

void LockTest2(void)
{
	// wrong: temp var, dtor guard immediately
	lock_guard<mutex> { mtx }; // same as (lock_guard<mutex>) mtx;
	(lock_guard<mutex>) mtx;
	// right: local guard
	lock_guard<mutex> g { mtx };
	cout << "aaa" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "bbb" << endl;
}

void LockTest(void)
{
	CVTestNoPred();
	CVTest();

	thread t(LockTest2);
	thread t2(LockTest2);

	t.join();
	t2.join();
}

