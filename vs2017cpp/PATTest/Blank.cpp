#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> name;
vector<string> si;
vector<string> so;


int main(void)
{
	int n = 0;
	cin >> n;
	string s1, s2, s3;
	for (int i = 0; i < n; ++i)
	{
		cin >> s1 >> s2 >> s3;
		name.push_back(s1);
		si.push_back(s2);
		so.push_back(s3);
	}

	auto simin = min_element(si.begin(), si.end());
	auto namemin = name[simin - si.begin()];
	auto somax = max_element(so.begin(), so.end());
	auto namemax = name[somax - so.begin()];
	cout << namemin << " " << namemax << endl;
}