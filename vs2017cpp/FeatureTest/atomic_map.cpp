#include <atomic>
#include <unordered_map>

using namespace std;

void AtomicMapTest();


int g_nAtomicMapLen = 10;
atomic<unordered_map<int, int>*> g_pAtomicMap;



void atomicMapLoad(int factor)
{
	int len = g_nAtomicMapLen;
	auto p = new unordered_map<int, int>;
	auto& m = *p;
	for (int i = 0; i < len; i++)
	{
		m[i] = factor * i;
	}
	g_pAtomicMap.store(p);
}

void atomicMapPrint(void)
{
	auto p = g_pAtomicMap.load();
	printf("map: ");
	for (auto iter = p->begin(); iter != p->end(); iter++) {
		printf("%d:%d ", iter->first, iter->second);
	}
	puts("");
}

void AtomicMapTest()
{
	atomicMapLoad(4);
	atomicMapPrint();
	atomicMapLoad(6);
	atomicMapPrint();
}