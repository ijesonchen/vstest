#include <mutex>
#include <memory>
#include <iostream>
using namespace std;

struct testc {
	testc(int x):m(x) { cout << "ctor " << m << endl; }
	~testc() { cout << "dtor " << m << endl; }
	int m = -1;
};

mutex gpmu;
shared_ptr<testc> gp;
 

void init() {
	shared_ptr<testc>  t (new testc(10));
	cout << "use_count: " << (t).use_count() << " data: " << (t).get()->m << endl;
	gpmu.lock();
	gp = t;
	gpmu.unlock();
	cout << "atomic_store" << endl;
}

void get() {
	gpmu.lock();
	auto p = gp;
	gpmu.unlock();
	if (p) {
		cout<< "use_count: " << (p).use_count() <<" data: "<< (p).get()->m << endl;
	}
	else {
		cout << "no data" << endl;
	}
}

static int x = 10;
void set() {
	x++;
	
	shared_ptr<testc>  t(new testc(x));

	gpmu.lock();
	auto p = gp;
	gp = t;
	gpmu.unlock();

	if (p) {
		cout << " has data use_count: " << p.use_count() << " data: " << p.get()->m << endl; 
	} 
}

void reset() {
	shared_ptr<testc>  t;
	gpmu.lock(); 
	gp = t;
	gpmu.unlock();
}


shared_ptr<testc> puse;
void use() {
	gpmu.lock();
	puse = gp;
	gpmu.unlock();
	if (puse) {
		cout << " use data use_count: " << puse.use_count() << " data: " << puse.get()->m << endl;
	}

}
void deuse() {
	puse.reset();
	cout << " de use data use_count: " << puse.use_count() << endl;
}

shared_ptr<testc> new1() {
	cout << "new1" << endl;
	shared_ptr<testc> p(new testc(++x));
	return p;
}


void new2() {
	cout << "new2" << endl;
	shared_ptr<testc> p(new testc(++x));
	cout << "new1 call" << endl; 
	p = new1();
	cout << "new1 return" << endl;
}

#ifdef _linux

int main() {
	cout << "===>get" << endl;
	get();
	cout << "===>set" << endl;
	set();
	cout << "===>use" << endl;
	use();
	cout << "===>init" << endl;
	init();
	cout << "===>deuse" << endl;
	deuse();
	cout << "===>get" << endl;
	get();
	cout << "===>set" << endl;
	set();
	cout << "===>get" << endl;
	get();
	cout << "===>reset" << endl;
	reset();
	cout << "===>get" << endl;
	get();
	cout << "===>new2" << endl;
	new2();
	cout << "===>exit" << endl;

}


#endif // _linux