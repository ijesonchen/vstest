#include "patMain.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(void)
{
	Main();
	std::cout << "Press enter";
	std::getchar();
}

//////////////////////////////////////////////////////////////////////////
// redirect file to cin
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

//////////////////////////////////////////////////////////////////////////
// tick tock 
chrono::steady_clock::time_point g_timepoint;
void Tick(void)
{
	g_timepoint = chrono::high_resolution_clock::now();
}

void Tock(void)
{
	auto cost = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - g_timepoint).count();;
	cout << "cost: " << cost << " seconds." << endl;
	Tick();
}