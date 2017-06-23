#include <iostream>
#include <functional>
#include <memory>
#include <string>

//////////////////////////////////////////////////////////////////////////
/*
both ReturnGuard and ScopeGuard can be used.
guard function will executed when caller function return.
use Release() to avoid execution of guard function with ReturnGuard

ReturnGuard must specific an ReturnExecutor variable name
ScopeGuard will gen an anonymous variable name with line number like
	_anonymous_93 (suppose ScopeGuard is called in line 93)
*/

using namespace std;

// gen anonymous name with line number:  _anonymous_($LineNumber)
#define __ANONYMOUS(type,ann,line)	type ann##line
#define	_ANONYMOUS(type,line)		__ANONYMOUS(type,_anonymous_,line)
#define	ANONYMOUS(type)				_ANONYMOUS(type,__LINE__)

#define	ScopeGuard( func )			ANONYMOUS(ReturnExecutor)([&](){func; });

// ReturnExecutor var([&](){ f; })
#define ReturnGuard(name, func)	\
		ReturnExecutor name([&](){ func; });


class ReturnExecutor
{
public:
	ReturnExecutor(ReturnExecutor& another) = delete;
	ReturnExecutor& operator=(ReturnExecutor&) = delete;

	ReturnExecutor() {};
	ReturnExecutor(ReturnExecutor&& another) { f = std::move(another.f); };
	void operator=(ReturnExecutor&& another) { f = std::move(another.f); };

	ReturnExecutor(std::function<void()> i) :f(std::move(i)){}

	~ReturnExecutor(void){ if (f) f(); }

	void Release(void) { f = nullptr; }	
private:
	std::function<void()> f = nullptr;
};


class RMClient
{
public:
	RMClient(const std::string& s)
		:name(s)
	{
		surfix = string(typeid(*this).name()) + "_" + name + ": ";
		cout << surfix << " ctor" << endl;
	}

	~RMClient()
	{
		cout << surfix << " dtor" << endl;
	}

	void RecvMsg(std::string& msg)
	{
		cout << "\t" << "before RecvMsg" << endl;
		cout << "\t\t" << surfix << "RecvMsg " << msg << endl;

		ScopeGuard(SendMsg(msg));

		ReturnGuard(t1, SendMsg(msg));
		t1.Release();

		cout << "\t" << "after RecvMsg" << endl;

		msg = "afterMsgChanged";
	}

	void SendMsg(const std::string& msg)
	{
		cout << "\t\t" << surfix << "SendMsg " << msg << endl;
	}
private:
	std::string name;
	std::string surfix;
};

void ResourceManage(void)
{
	RMClient rmClient("rm");

	string s("TestMsg");


	rmClient.RecvMsg(s);

	ReturnGuard(t1, rmClient.SendMsg(s));
	auto t2 = std::move(t1);

	decltype(t2) t3;
	t3 = std::move(t2);

	s = "test2";
	cout << "after ResourceManage" << endl;

}