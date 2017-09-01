#include <windows.h>
#include <iostream>
#include <cstdio>

using namespace std;

void ConsoleColorTest(void)
{
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);//设置为红色
	printf("red\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);//恢复默认
	printf("default\n");

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);//设置为红色
	cout << "red" << endl;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);//恢复默认
	cout << "default" << endl;
}