#include <memory>
#include <atomic>
#include <unordered_map>
using namespace std;
void AtomicRaiiTest();

struct AtomicRaiiS;

//atomic<shared_ptr<unordered_map<int, int>*>> g_pAtomicRaiiMap;
shared_ptr<AtomicRaiiS> g_spRaiiStru;

struct AtomicRaiiS {
public:
	AtomicRaiiS() { id = 0; puts("new AtomicRaiiS"); }
	AtomicRaiiS(int factor, size_t len) {
		id = factor * len;
		printf("new AtomicRaiiS with param %d %zd\n", factor, len);
		m.reserve(len);
		for (int i = 0; i < len; i++)
		{
			m[i] = factor * i;
		}
		Print();
	}
	void Print(void) {
		printf("data: ");
		for (auto p = m.begin(); p != m.end(); p++)
		{
			printf("%d:%d ", p->first, p->second);
		}
		puts("");
	}
	~AtomicRaiiS() { printf("remove AtomicRaiiS %zd\n", id); }\

	unordered_map<int, int> m;
private:
	size_t id;
};

void AtomicRaiiLoad(int x) {
	shared_ptr< AtomicRaiiS> sp(new AtomicRaiiS(x, 5));
	atomic_store(&g_spRaiiStru, sp);
}



int LoadModel(int n) {
	shared_ptr< AtomicRaiiS> sp(new AtomicRaiiS(n, 5));
	atomic_store(&g_spRaiiStru, sp);
	return 0;
}

int ProcData(void* pvinInt, void* pvoutFloat, size_t nLen) {
	auto pIn = (int64_t*)pvinInt;
	auto pOut = (float*)pvoutFloat;
	auto spData = atomic_load(&g_spRaiiStru);
	auto& m = spData->m;
	for (auto i = 0; i < nLen; i++) {
		pOut[i] = m[pIn[i]];
	}
	return 0;
}

void AtomicRaiiTest()
{ 
	unordered_map<int, int> m;
	m[5] = 3;
	printf("map 5 %d", m[5]);
	printf("map 10 %d", m[10]);
	auto p = atomic_load(&g_spRaiiStru);
	if (p){
		p->Print();
	}
	else {
		puts("nil pointer");
	}
	AtomicRaiiLoad(3);
	AtomicRaiiLoad(4);
	AtomicRaiiLoad(5);
	p = atomic_load(&g_spRaiiStru);
	p->Print();
}