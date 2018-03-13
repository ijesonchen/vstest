/*
1088. Rational Arithmetic (20)
200 ms
65536 kB

14:30

For two rational numbers, your task is to implement the basic arithmetics, that is,
to calculate their sum, difference, product and quotient.

Input Specification:

Each input file contains one test case, which gives in one line the two rational numbers in the format "a1/b1 a2/b2". 
The numerators and the denominators are all in the range of long int. 
If there is a negative sign, it must appear only in front of the numerator. 
The denominators are guaranteed to be non-zero numbers.

Output Specification:

For each test case, print in 4 lines the sum, difference, product and quotient of the two rational numbers, respectively.
The format of each line is "number1 operator number2 = result". 
Notice that all the rational numbers must be in their simplest form "k a/b",
where k is the integer part, and a/b is the simplest fraction part. 
If the number is negative, it must be included in a pair of parentheses. 
If the denominator in the division is zero, output "Inf" as the result. 
It is guaranteed that all the output integers are in the range of long int.

Sample Input 1:
2/3 -4/2
Sample Output 1:
2/3 + (-2) = (-1 1/3)
2/3 - (-2) = 2 2/3
2/3 * (-2) = (-1 1/3)
2/3 / (-2) = (-1/3)
Sample Input 2:
5/3 0/6
Sample Output 2:
1 2/3 + 0 = 1 2/3
1 2/3 - 0 = 1 2/3
1 2/3 * 0 = 0
1 2/3 / 0 = Inf
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

/*
14:20
实现分数四则运算
真分数，约掉 k a/b
负数加括号
除0得inf
long范围(int64_t?)

15：25 FAIL 四则运算时，注意k

*/
namespace nsA1088A
{
	long SimpleNum(long a, long b)
	{
		long c = a / b;
		if (a==b*c)
		{
			return c;
		}
		return 0;
	}
	struct Rational
	{
		bool neg = false;
		long k = 0;
		long a = 0;
		long b = 0;

		Rational(int m, int n): a(m), b(n)
		{
			Simplify();
		}

		string Print(void)
		{
			if (a==0 && k==0)
			{
				return "0";
			}
			stringstream ss;
			string sp1, sp2;
			if (neg)
			{
				sp1 = "(-", sp2 = (")");
			}
			ss << sp1;
			// (-k a/b)
			if (k)
			{
				ss << k;
			}
			if (k && a)
			{
				ss << " ";
			}
			if (a)
			{
				ss << a << "/" << b;
			}
			ss << sp2;
			return ss.str();
		}

		void Simplify(void)
		{
			if (b<0)
			{
				a = -b;
				b = -b;
			}
			if (a < 0)
			{
				neg = true;
				a = -a;
			}
			if (a > b)
			{
				k = a / b;
				a = a % b;
			}
			bool loop = true;
			while (loop)
			{
				loop = false;
				long n = (long)sqrt(b) + 1;
				for (int i = 2; i < n && i <= a; ++i)
				{
					long a1 = SimpleNum(a, i);
					long b1 = SimpleNum(b, i);
					if (a1&&b1)
					{
						a = a / a1;
						b = b / b1;
						loop = true;
						break;
					}
				}
			}
		}
	};

	Rational Sub(Rational r1, Rational r2);
	Rational Add(Rational r1, Rational r2)
	{
		if (!r1.neg && !r2.neg)
		{
			long a = r1.a + r2.a;
			long b = r1.b + r2.b;
			return Rational(a, b);
		}
		if (r1.neg&&r2.neg)
		{
			long a = r1.a + r2.a;
			long b = r1.b + r2.b;
			return Rational(-a, b);
		}
		if (!r1.neg&&r2.neg) // + -
		{
			r2.neg = false;
			return Sub(r1, r2);
		}
		if (r1.neg&&!r2.neg) // - +
		{
			r1.neg = false;
			return Sub(r2, r1);
		}
		throw 0;
		return Rational(0, 0);
	}

	Rational Sub(Rational r1, Rational r2)
	{
		if (!r1.neg && !r2.neg) // + +
		{
			long a = r1.a - r2.a;
			long b = r1.b - r2.b;
			return Rational(a, b);
		}
		if (r1.neg&&r2.neg) // - -
		{
			long a = r1.a + r2.a;
			long b = r1.b + r2.b;
			return Rational(-a, b);
		}
		if (!r1.neg&&r2.neg) // + -
		{
			r2.neg = false;
			return Add(r1, r2);
		}
		if (r1.neg && !r2.neg) // - +
		{
			r2.neg = true;
			return Add(r1, r2);
		}
		throw 0;
		return Rational(0, 0);
	}

	Rational Div(Rational r1, Rational r2);
	Rational Mul(Rational r1, Rational r2)
	{
		if (!r1.neg && !r2.neg ||// + +
			r1.neg&&r2.neg)  // - -
		{
			long a = r1.a*r2.a;
			long b = r1.b*r2.b;

		}
		if (!r1.neg&&r2.neg) // + -
		{
			r2.neg = false;
			return Add(r1, r2);
		}
		if (r1.neg && !r2.neg) // - +
		{
			r2.neg = true;
			return Add(r1, r2);
		}
		throw 0;
		return Rational(0, 0);
	}

	void main(void)
	{
		long a1, b1, a2, b2;
		scanf("%ld/%ld %ld/%ld", &a1, &b1, &a2, &b2);
		Rational a(a1, b1), b(a2, b2);
		string s1 = a.Print(), s2 = b.Print();
	}
}


/*
15:45
0. 使用纯分数计算，使用带分数打印
1. 判断是否为0
2. 分子带符号，除法变乘法（注意符号）
16:20 35MIN 8/20 WA0,2

bug-fix-1: 求最大公约数时，应该从min(a,b)开始往回找
16:35 15min 14/20 WA2 TLE3

improve-1
谷歌最大公约数：
gcd(a,b) = gcd(b, a%b)
16:55 20min 17/20 WA2
*/

namespace nsA1088B
{

	int gcd(long a, long b)
	{
		if (b==0)
		{
			return a;
		}
		return gcd(b, a%b);
	}

	struct Rational 
	{
		long a = 0;
		long b = 0;

		Rational(int u, int v):a(u),b(v)
		{
			if (b < 0) { throw 0; }
			if (a == 0) { b = 1; }
		}

		bool IsZero(void) { return a == 0; }

		void Turn(void)
		{
			swap(a, b);
			if (b < 0)
			{
				a = -a;
				b = -b;
			}
		}

		void Print(void) 
		{
			if (b == 0) // inf
			{ 
				printf("Inf");
				return;
			}
			if (a == 0) // 0
			{ 
				printf("0");
				return;
			}

			if (a<0)
			{
				printf("(");
			}
			if (a / b * b == a) // 整数
			{
				printf("%d", a / b); 
				if (a < 0) { printf(")"); }
				return; 
			}

			long k = 0;
			long u = a;
			long v = b;
			if (abs(u)>v)
			{
				k = u / v;
				u = abs(u);
				u = u % v;
			}

			// bug-fix-1
// 			long t = std::min(abs(u), v);
// 			for (long i = t; i > 1; --i)
// 			{
// 				if ((u/i*i==u) && (v/i*i==v))
// 				{
// 					u = u / i;
// 					v = v / i;
// 					break;
// 				}
// 			}
			// improve-1
			long t = abs(gcd(u, v));
			u /= t;
			v /= t;
			if (k) { printf("%d ", k); }
			printf("%d/%d", u, v);
			if (a < 0) { printf(")"); }
		};
	};

	void Add(Rational r1, Rational r2)
	{
		int a = r1.a*r2.b + r1.b*r2.a;
		int b = r1.b*r2.b;
		Rational r(a, b);
		r1.Print();
		cout << " + ";
		r2.Print();
		cout << " = ";
		r.Print();
		cout << endl;
	}

	void Sub(Rational r1, Rational r2)
	{
		int a = r1.a*r2.b - r1.b*r2.a;
		int b = r1.b*r2.b;
		Rational r(a, b);
		r1.Print();
		cout << " - ";
		r2.Print();
		cout << " = ";
		r.Print();
		cout << endl;
	}

	void Mul(Rational r1, Rational r2)
	{
		int a = r1.a*r2.a;
		int b = r1.b*r2.b;
		Rational r(a, b);
		r1.Print();
		cout << " * ";
		r2.Print();
		cout << " = ";
		r.Print();
		cout << endl;
	}
	
	void Div(Rational r1, Rational r2)
	{
		Rational tmp(r2);
		r2.Turn();
		int a = r1.a*r2.a;
		int b = r1.b*r2.b;
		Rational r(a, b);
		r1.Print();
		cout << " / ";
		tmp.Print();
		cout << " = ";
		r.Print();
		cout << endl;
	}

	void main(void)
	{
		long a, b;
		scanf("%ld/%ld", &a, &b);
		Rational r1(a, b);
		scanf("%ld/%ld", &a, &b);
		Rational r2(a, b);
		Add(r1, r2);
		Sub(r1, r2);
		Mul(r1, r2);
		Div(r1, r2);
	}
}

// rename this to main int PAT
int A1088Func(void)
{
	nsA1088B::main();
	return 0;
}


void A1088(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1088Func();
	cout << endl;
}

void A1088(void)
{
//	A1088("data\\A1088-1.txt"); // 
//	A1088("data\\A1088-2.txt"); // 
	A1088("data\\A1088-3.txt");
}

