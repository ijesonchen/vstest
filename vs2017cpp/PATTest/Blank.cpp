#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <numeric>

using namespace std;

const int A1016HourCount = 24;

vector<int> A1016vtCost;
int A1016nDayCost = 0;

struct A1016Record
{
	string time;
	bool off = false;

	A1016Record(string s, bool o) :time(s), off(o) {};
};

bool operator<(const A1016Record& lhs, const A1016Record& rhs)
{
	return lhs.time < rhs.time;
}

bool A1016IsOffline(const string& s)
{
	return s[1] == 'f';
}

int A1016HourCost(int h1, int h2)
{
	int total = 0;
	for (int h = h1; h < h2; ++h)
	{
		total += 60 * A1016vtCost[h];
	}
	return total;
}

int A1016Time2Min(const string& s1)
{
	const int d1 = atoi(s1.substr(3, 2).c_str());
	const int h1 = atoi(s1.substr(6, 2).c_str());
	const int m1 = atoi(s1.substr(9, 2).c_str());
	return (d1 * 24 + h1) * 60 + m1;
}

int A1016PrintCharge(const string& s1, const string& s2)
{
	int total = 0;
	auto t1 = s1.substr(3);
	auto t2 = s2.substr(3);
	auto minu = A1016Time2Min(s2) - A1016Time2Min(s1);
	// d h m  00:00:00
	const int d1 = atoi(t1.substr(0, 2).c_str());
	const int h1 = atoi(t1.substr(3, 2).c_str());
	const int m1 = atoi(t1.substr(6, 2).c_str());
	const int d2 = atoi(t2.substr(0, 2).c_str());
	const int h2 = atoi(t2.substr(3, 2).c_str());
	const int m2 = atoi(t2.substr(6, 2).c_str());
	int day = d2 - d1;
	bool twoPart = t1.substr(3) > t2.substr(3);
	if (twoPart)
	{
		--day;
		total += (60 - m1) * A1016vtCost[h1];
		total += A1016HourCost(h1 + 1, 24);
		total += A1016HourCost(0, h2 - 1);
		total += m2* A1016vtCost[h2];
	}
	else
	{
		if (h1 == h2)
		{
			total += (m2 - m1)*A1016vtCost[h1];
		}
		else
		{
			total += (60 - m1) * A1016vtCost[h1];
			total += A1016HourCost(h1 + 1, h2);
			total += m2* A1016vtCost[h2];
		}
	}
	total += day * A1016nDayCost;

	cout << t1 << " " << t2;
	printf(" %d $%.2f\n", minu, (float)total / 100);

	if (!total)
	{
		throw 0;
	}
	return total;
}

void A1016PrintBill(const string& name, const set<A1016Record>& setRec)
{
	auto it = setRec.begin();
	while (it != setRec.end() && it->off)
	{
		++it;
	}
	if (it == setRec.end())
	{
		return;
	}

	auto first = it++;
	bool header = false;

	int total = 0;

	for (; it != setRec.end(); ++it)
	{
		if (!it->off)
		{
			first = it;
			continue;
		}
		if (!header)
		{
			cout << name << " " << first->time.substr(0, 2) << endl;
			header = true;
		}
		total += A1016PrintCharge(first->time, it->time);

		do
		{
			++it;
		} while (it != setRec.end() && it->off);
		if (it == setRec.end())
		{
			break;
		}
		first = it;
	}
	if (total)
	{
		cout << "Total amount: $";
		printf("%.2f\n", float(total) / 100);
	}
}

// rename this to main int PAT
int main(void)
{
	A1016vtCost.clear();
	for (int i = 0; i < A1016HourCount; ++i)
	{
		int tmp;
		cin >> tmp;
		A1016vtCost.push_back(tmp);
	}

	A1016nDayCost = std::accumulate(A1016vtCost.begin(), A1016vtCost.end(), 0);
	A1016nDayCost *= 60;

	map<string, set<A1016Record>> mData;

	int rec;
	cin >> rec;
	for (int i = 0; i < rec; ++i)
	{
		// name time tag
		string name, time, stag;
		cin >> name >> time >> stag;
		auto tag = A1016IsOffline(stag);
		mData[name].insert(A1016Record(time, tag));
	}

	for (auto& user : mData)
	{
		A1016PrintBill(user.first, user.second);
	}

	return 0;
}