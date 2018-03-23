#include "patMain.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;


int main(void)
{
	std::cout << "Press enter";
	std::getchar();
}

//////////////////////////////////////////////////////////////////////////
// redirect file to cin
ifstream g_fRedirCin;
FILE* g_fReopen = nullptr;
void RedirCin(const std::string& fn)
{
	if (g_fReopen) { fclose(g_fReopen); }
	g_fReopen = freopen(fn.c_str(), "r", stdin);
	cin.clear();
	return;
	g_fRedirCin.close();
	g_fRedirCin.open(fn);
	if (!g_fRedirCin)
	{
		abort();
	}
	cin.rdbuf(g_fRedirCin.rdbuf());
}

//////////////////////////////////////////////////////////////////////////
// tick tock 
chrono::steady_clock::time_point g_timepoint;
void Tick2(void)
{
	g_timepoint = chrono::high_resolution_clock::now();
}

void Tock2(void)
{
	auto cost = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - g_timepoint).count();;
	cout << "cost: " << cost << " seconds." << endl;
	Tick2();
}