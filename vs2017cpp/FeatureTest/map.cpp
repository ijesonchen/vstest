#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <time.h>
#include <stdlib.h>

using namespace std;

void debug_print(int& v);

template <class T>
void debug_print_map_key(T& m) {
	for (auto& it : m) {
		printf("%s, ", it.first.c_str());
	}
}

template <class T>
void debug_print_continer_str(T& m) {
	for (auto& it : m) {
		printf("%s, ", it.c_str());
	}
}

template <class T>
void debug_print_map_kv(T& m) {
	for (auto& it : m) {
		printf("%s:", it.first.c_str());
		debug_print(it.second);
	}
}

void TestMapOrder(void) {
	int loop = 10;
	srand(time(nullptr));
	map<int, int> m;
	for (int i = 0; i < loop; i++) {
		m[rand()] = rand();
	}
	for (auto& it : m) {
		cout << it.first << " " << it.second << endl;
	}
}

void TestMap() {
	TestMapOrder();
	using WorkerMap = std::map<std::string, int>;

	WorkerMap w;
	w["kkk"] = 1;
	w["ttt"] = 2;
	printf("WorkerMap w: ");
	debug_print_map_key(w);
	puts("");
	printf("WorkerMap2 w: ");
	debug_print_map_kv(w);
	puts("");



	std::vector<std::string> fea_keys_{"aaa", "bbb"};
	printf("fea_keys_: ");
	debug_print_continer_str(fea_keys_);
	puts("");
	std::unordered_set<std::string> config_keys_{ "ccc", "ddd" };
	printf("config_keys_: ");
	debug_print_continer_str(config_keys_);
	puts("");
}