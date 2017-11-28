#ifndef common_h__
#define common_h__

#include <ctime>
#include <string>
#include <functional>

std::string Timet2String(time_t tm);

#define ReturnGuard(name, func)	\
		ReturnExecutor name([&](){ func; });

class ReturnExecutor
{
	ReturnExecutor(ReturnExecutor& another) = delete;
public:
	ReturnExecutor(std::function<void()> i) :f(std::move(i)) {}
	~ReturnExecutor(void) { if (f) f(); }

	void Release(void) { f = nullptr; }
private:
	std::function<void()> f = nullptr;
};

#endif // common_h__
