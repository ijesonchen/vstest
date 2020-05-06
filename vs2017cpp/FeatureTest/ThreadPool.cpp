#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <deque>
#include <sstream>
#include <condition_variable>
#include "chrono.h"

void ThreadPoolTest(void);

using namespace std;
string AppTime(void);

class WaitGroup {
	atomic_int x;
	mutex m;
	condition_variable cv;
public:
	WaitGroup() { x.store(0); }
	void Add(int n) {
		x += n;
		cout << "add " << x << endl;
	}
	void Done() {
		x--;
		if (x == 0) {
			cout << AppTime() << "wg notify" << endl;
			cv.notify_all();
		}
	}
	void Wait() {
		std::unique_lock<std::mutex> lock(m);
		cv.wait(lock, [&] { return x <= 0; });

	}
};

class ITask {
public:
	virtual ~ITask() {};
	virtual bool Run(int tid)=0;
};

class CharTask: public ITask {
	string name;
	int    val;
	WaitGroup* wg;
public:
	~CharTask() {};
	CharTask(const char* p, int x, WaitGroup* w) {
		name = p;
		val = x; 
		wg = w;
	}  
	bool Run(int tid) {
		/*stringstream ss;
		//ss << AppTime() << tid << " enter proc " << name << val << endl;
		//cout << ss.str();
		auto r = rand();
		this_thread::sleep_for(chrono::milliseconds(500 + r % 30));
		ss.str("");
		ss << AppTime() << tid << " leave proc " << name << val << endl;
		cout << ss.str();*/
		wg->Done();
		return true;
	}
};

class BusyTask : public ITask { 
public:
	~BusyTask() {};
	BusyTask() {};
	bool Run(int tid) {
		uint64_t k = 0;
		while (true) {
			auto x = rand();
			if ((x % 10000)==0) {
				k++;
			}
			if ((k % 10000) == 0) {
				k++;
				cout << k << endl;
			}
		}
		return true;
	}
};

class ThreadMgr {
	int mgrid = rand();
public:
	ThreadMgr(int nThread) {
		running = true;
		for (int i = 0; i < nThread; i++) {
			threadPool.push_back(std::move(thread(ThreadFunc, this, i)));
		}
	}

	~ThreadMgr() {
		running = false;
		cvSig.notify_all();
		for (auto& t : threadPool) {
			t.join();
		}
	}

	void AddTask(vector<shared_ptr<ITask>>v) {
		mTasks.lock(); 
		for (size_t i = 0; i < v.size(); i++) {
			deTasks.push_front(v[i]);
		}
		mTasks.unlock();
		cvSig.notify_all();
	}

	void AddTask(shared_ptr<ITask>& sp) {
		mTasks.lock();
		deTasks.push_front(sp);
		mTasks.unlock();
		cvSig.notify_all();
	}
private:
	static void ThreadFunc(ThreadMgr* mgr, int tid) {
		stringstream ss;
		ss << AppTime() << "thread enter: " << tid << endl;
		cout << ss.str();
		auto& deTasks = mgr->deTasks;
		auto& lk = mgr->mTasks;
		auto& cv = mgr->cvSig;
		auto& lksig = mgr->mSig;
		while (mgr->running){
			shared_ptr<ITask> p;
			lk.lock();
			if (deTasks.size() > 0) {
				p = deTasks.back();
				deTasks.pop_back();
			}
			lk.unlock();
			if (!p) {
				std::this_thread::sleep_for(std::chrono::microseconds(100));
				//std::unique_lock <std::mutex> lck(lksig);
				//cv.wait(lck);
				continue;
			}
			p->Run(tid);
		}
		ss.str("");
		ss << AppTime() << "thread leave: " << tid << endl;
		cout << ss.str();
	}
	vector<thread> threadPool;
	atomic_bool			running;
	mutex				mSig;
	condition_variable  cvSig;
	deque<shared_ptr<ITask>> deTasks;
	mutex         mTasks;
};

void ThreadPoolMain() {
	cout << AppTime() << "ThreadPoolMain enter" << endl;
	auto mgr = new ThreadMgr(6);
	this_thread::sleep_for(chrono::seconds(1));

	for (int i = 0; i < 5; i++) {
		shared_ptr<ITask> busyTask = make_shared<BusyTask>();
		mgr->AddTask(busyTask);
	}

	const auto jLoop = 3;
	WaitGroup wg[jLoop];
	for (int j = 0; j < jLoop; j++) {
		int loop = 100;
		vector<shared_ptr<ITask>> v;
		wg[j].Add(loop);
		for (int i = 0; i < loop; i++) {
			v.push_back(make_shared<CharTask>("test", j*loop+i, &wg[j]));
		}
		cout << AppTime() << "main sleep" << endl;
		this_thread::sleep_for(chrono::seconds(3));

		cout << AppTime() << "main add task" << endl;
		Ticker t; 
		mgr->AddTask(v);
		auto cost1 = t.TockNoRecord();
		//wg.Wait();
		wg[j].Wait();
		auto cost2 = t.TockNoRecord();
		cout << AppTime() << "main wait " << cost1 << " " << cost2 << endl;
		//this_thread::sleep_for(chrono::seconds(1));
	}

	for (int j = 0; j < jLoop; j++) {
		wg[j].Wait();
	}


	cout << AppTime() << "delete mgr";
	delete mgr;
}

void ThreadPoolTest(void) {
	ThreadPoolMain();
}