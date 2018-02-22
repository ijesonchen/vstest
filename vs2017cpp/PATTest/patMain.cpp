#include "patMain.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(void)
{
	A1031();
	std::cout << "Press enter";
	std::getchar();
}

void Basic(void) { B1003(); }
void Advanced(void) { A1138(); }
void Top(void) { T1001(); }
void PatMain(void) { Advanced(); }

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