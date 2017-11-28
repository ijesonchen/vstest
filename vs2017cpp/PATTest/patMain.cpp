#include "patMain.h"
#include <iostream>
#include <fstream>

using namespace std;
ifstream g_fRedirCin;
void RedirCin(const std::string& fn)
{
	g_fRedirCin.close();
	g_fRedirCin.open(fn);
	if (!g_fRedirCin)
	{
		abort();
	}
	cin.rdbuf(g_fRedirCin.rdbuf());
}

int main(void)
{
	Main();
	std::cout << "Press enter";
	std::getchar();
}