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

private:
	unordered_map<int, int> m;
	size_t id;
};

void AtomicRaiiLoad(int x) {
	shared_ptr< AtomicRaiiS> sp(new AtomicRaiiS(x, 5));
	atomic_store(&g_spRaiiStru, sp);
}

void AtomicRaiiTest()
{ 
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