#include <string>
#include <iostream>

void StringTest(void);

using namespace std;

/*
0. string内部存储会多1字节，方便data(), c_str()转换为0尾的char*。
1. 优化：部分实现预分配16字节栈空间，末尾留0。长度15以内直接使用。
2. (p, len)构造会拷贝内存。
*/

void StringTest(void) {
	int len = 16;
	auto p = new char[len];
	for (int i = 0; i < len; i++) {
		p[i] = 'a' + i;
	}
	string s(p, len); 
	printf("p %p s %p %p %zd\n", p, s.data(), s.c_str(), s.length());
	delete []p;
	p = s.data();
	printf("hex %x %x %x %x %x\n", p[0], p[1], p[2], p[3], p[len]);
	cout << s << endl;
}