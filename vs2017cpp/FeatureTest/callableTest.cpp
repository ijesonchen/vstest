#include <iostream>
#include <functional>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////
/*
1. function<T> 可以支持函数、可调用类，lambda表达式等
2. 可调用类赋值给function<T>时会引起两次构造：
	准备对象用于swap（默认copy，可move），随后被析构
	存储于function
3. lambda表达式捕获[]可选 赋值= 或 引用&
4. function容器存储可调用对象时，最好预先reserve容量，否则自动扩容容易引起可调用对象的构造
*/

using namespace std;


using TCallAble = function<void()>;

void CallAbleFunc(void)
{
	cout << "called: CallAbleFunc" << endl;
}

class CallAbleClass
{
public:
	CallAbleClass(const string& _s) :s(_s) {};
	~CallAbleClass() 
	{
		cout << "CallAbleClass: dtor." << s << endl;
	};

	CallAbleClass(const CallAbleClass& other)
	{
		cout << "CallAbleClass: copy ctor from " << other.s << endl;
		s = other.s + " copy";
	}

	CallAbleClass(CallAbleClass&& other)
	{
		cout << "CallAbleClass: move ctor from " << other.s << endl;
		s = other.s + " move";
	}

	CallAbleClass& operator=(const CallAbleClass& other)
	{
		cout << "CallAbleClass: copy assign from " << other.s << endl;
		s = other.s + " copy=";
	}

	CallAbleClass& operator=(CallAbleClass&& other)
	{
		cout << "CallAbleClass: move assign from " << other.s << endl;
		s = other.s + " move=";
	}

	void operator()(void)
	{
		cout << "called: CallAbleClass: " << s << endl;
		s += " call";
	}

private:
	string s;
};

void FunctionTest()
{
	function<void()> f1;
	function<void()> f2;


	cout << "**CallAbleFunc test" << endl;
	f1 = CallAbleFunc;
	f1();

	cout << "**CallAbleClass test" << endl;

	CallAbleClass c("classParam");
	cout << "copy callable: " << endl;
	f1 = c;
	f1();
	cout << endl;

	cout << "move callable: " << endl;
	f1 = std::move(c);
	f1();
	cout << endl;

	// release callable class (will invoke dtor)
	f1 = nullptr;

	cout << "**lambda test" << endl;

	string lambdaTestString = "lambda_beforeChange";
	f1 = [&lambdaTestString]() { cout << "called: " << lambdaTestString << endl; };
	f2 = [=]() { cout << "called: " << lambdaTestString << endl; };

	lambdaTestString = "lambda_afterChange.";

	f1();
	f2();

	cout << endl;


	cout << "return" << endl;

	/*
	**CallAbleFunc test
	called: CallAbleFunc

	**CallAbleClass test
	copy callable:
	CallAbleClass: copy ctor.
	CallAbleClass: move ctor.
	CallAbleClass: dtor.classParam copy
	called: CallAbleClass: classParam copy move

	move callable:
	CallAbleClass: move ctor.
	CallAbleClass: move ctor.
	CallAbleClass: dtor.classParam move
	CallAbleClass: dtor.classParam copy move
	called: CallAbleClass: classParam move move

	CallAbleClass: dtor.classParam move move
	**lambda test
	called: lambda_afterChange.
	called: lambda_beforeChange

	return
	CallAbleClass: dtor.classParam
	*/
}

void VectorFunctionTest()
{
	vector<TCallAble> v;
	v.reserve(5);
	v.push_back(CallAbleFunc);

	cout << "    **cac1 move&push" << endl;
	v.push_back(std::move(CallAbleClass("classParam1")));

	cout << "    **cac2 move" << endl;
	TCallAble f = std::move(CallAbleClass("classParam2"));

	cout << "    **cac2 push" << endl;
	v.push_back(std::move(f));


	string lambdaTestString = "lambda_beforeChange";

	v.push_back([&lambdaTestString]() { cout << "called: " << lambdaTestString << endl; });
	v.push_back([=]() { cout << "called: " << lambdaTestString << endl; });

	lambdaTestString = "lambda_afterChange";

	cout << "data prepared. " << endl;
	for (auto& i : v)
	{
		i();
	}
	cout << "return" << endl;

	/*
	  **cac1 move&push
	CallAbleClass: move ctor from classParam1
	CallAbleClass: move ctor from classParam1 move
	CallAbleClass: dtor.classParam1 move
	CallAbleClass: dtor.classParam1
	  **cac2 move
	CallAbleClass: move ctor from classParam2
	CallAbleClass: move ctor from classParam2 move
	CallAbleClass: dtor.classParam2 move
	CallAbleClass: dtor.classParam2
	  **cac2 push
	CallAbleClass: copy ctor from classParam1 move move
	CallAbleClass: dtor.classParam1 move move
	CallAbleClass: copy ctor from classParam1 move move copy
	CallAbleClass: copy ctor from classParam2 move move
	CallAbleClass: dtor.classParam1 move move copy
	CallAbleClass: dtor.classParam2 move move
	CallAbleClass: copy ctor from classParam1 move move copy copy
	CallAbleClass: copy ctor from classParam2 move move copy
	CallAbleClass: dtor.classParam1 move move copy copy
	CallAbleClass: dtor.classParam2 move move copy

	data prepared.

	called: CallAbleFunc
	called: CallAbleClass: classParam1 move move copy copy copy
	called: CallAbleClass: classParam2 move move copy copy
	called: lambda_afterChange
	called: lambda_beforeChange

	return
	CallAbleClass: dtor.classParam1 move move copy copy copy
	CallAbleClass: dtor.classParam2 move move copy copy

	//////////////////////////////////////////////////////////////////////////
	with assign

	  **cac1 move&push
	CallAbleClass: move ctor from classParam1
	CallAbleClass: move ctor from classParam1 move
	CallAbleClass: dtor.classParam1 move
	CallAbleClass: dtor.classParam1
	  **cac2 move
	CallAbleClass: move ctor from classParam2
	CallAbleClass: move ctor from classParam2 move
	CallAbleClass: dtor.classParam2 move
	CallAbleClass: dtor.classParam2
	  **cac2 push
	CallAbleClass: copy ctor from classParam1 move move
	CallAbleClass: dtor.classParam1 move move

	data prepared.

	called: CallAbleFunc
	called: CallAbleClass: classParam1 move move copy
	called: CallAbleClass: classParam2 move move
	called: lambda_afterChange
	called: lambda_beforeChange

	return
	CallAbleClass: dtor.classParam1 move move copy
	CallAbleClass: dtor.classParam2 move move

	*/
}

void VectorFunctionCallAbleClassTest()
{
	vector<TCallAble> v;
	v.reserve(20); // without this, push will cause lots of ctor

	cout << "    **cac1 move&push" << endl;
	int i = 0;
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam1")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam2")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam3")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam4")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam5")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam6")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam7")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam8")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam9")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam10")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam11")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam12")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam13")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam14")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam15")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam16")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam17")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam18")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam19")));
	cout << ++i << endl;
	v.push_back(std::move(CallAbleClass("classParam20")));
	cout << ++i << endl;

	cout << "*****" << endl;
	for (auto& i : v)
	{
		i();
	}

	cout << "<<<<<" << endl;
	while (!v.empty())
	{
		v.pop_back();
		v.shrink_to_fit(); // with thi, resize vector will cause lots of ctor
	}

	cout << "****return" << endl;
}

void VectorFunctionCallAbleFuncTest()
{
	// function with vector, no reserve is ok
	vector<TCallAble> v;
	auto length = 10;
	cout << "**push " << endl;
	for (size_t i = 0; i < length; i++)
	{
		v.push_back(CallAbleFunc);
	}

	cout << "**call " << endl;
	for (auto i : v)
	{
		i();
	}

	cout << "**pop & shrink " << endl;
	while (!v.empty())
	{
		v.pop_back();
		v.shrink_to_fit();
	}

	cout << "return " << endl;
}

vector<TCallAble> PrePareVFLambda(void)
{
	CallAbleClass c("param1");

	vector<TCallAble> v;
	v.reserve(3);

	TCallAble f = ([c]() mutable
	{
		c();
	});
	v.push_back(f);
	v.push_back(f);
	v.push_back(f);

	return std::move(v);
}

void VFLambdaTest(void)
{
	auto v = PrePareVFLambda();
	cout << "**call" << endl ;
	for (auto& i : v)
	{
		i();
	}

	cout << endl;

	cout << " ** return **" << endl;
}

int FuncForBind(int x, const int y, CallAbleClass& c)
{
	cout << "input " << x << " " << y << endl;
	c();
	return x + y;
}

void SimpleBindTest(void)
{
	int a = 2;
	int b = 3;
	CallAbleClass c("param1");
	function<int()> n = bind(FuncForBind, a, b, std::move(c));



	a *= 2;
	b *= 3;

	cout << "call bind object: " << endl;
	cout << n() << endl;

	/*	
	CallAbleClass: move ctor from param1

	call bind object:
	input 2 3
	called: CallAbleClass: param1 move

	5

	CallAbleClass: dtor.param1 move call
	CallAbleClass: dtor.param1
	*/
}

template<typename F, typename ...Args>
std::function<void()> BindCallable(F&& f, Args&& ...args)
{
	auto call = std::bind(f, args ...); // this is acceptable in some case.
//	auto call = std::bind(std::forward<F>(f), std::forward<Args>(args) ...);
	// both return accepted.
	return [call]() mutable { cout << call() << endl; };
//	return call;
}

void ForwardBindTest(void)
{
	int a = 2;
	int b = 3;
	CallAbleClass c("param1");
	auto n = BindCallable(FuncForBind, a, b, std::move(c));

	cout << "  **call bind object: " << endl;
	n();
	cout << "  **return" << endl;

	/*	
	CallAbleClass: move ctor from param1
	CallAbleClass: copy ctor from param1 move
	CallAbleClass: move ctor from param1 move copy
	CallAbleClass: dtor.param1 move copy
	CallAbleClass: dtor.param1 move

	**call bind object:
	input 2 3
	called: CallAbleClass: param1 move copy move
	5	// if return lambda

	**return
	CallAbleClass: dtor.param1 move copy move call
	CallAbleClass: dtor.param1
	*/
}

void CallableTest(void)
{
	return;
	ForwardBindTest();
	SimpleBindTest();
	// lambda in vector<function<T>>
	VFLambdaTest();
	// test for function<T>
	FunctionTest();
	// vector<function<T>>
	VectorFunctionTest();
	// callable class in vector<function<T>>: try reserve capacity && not shrink, or will cause lots of ctor
	VectorFunctionCallAbleClassTest();
	// callable function in vector<function<T>>: shrink or no reserve is ok. 
	VectorFunctionCallAbleFuncTest();
}