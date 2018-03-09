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

// rename this to main int PAT
int A1088Func(void)
{
	nsA1088A::main();
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
	A1088("data\\A1088-1.txt"); // 
	A1088("data\\A1088-2.txt"); // 
}

