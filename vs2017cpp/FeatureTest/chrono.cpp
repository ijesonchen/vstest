#include <chrono>
#include <string>
#include <sstream>

void ChronoTest(void);
using namespace std;

auto appStart = chrono::high_resolution_clock::now();

uint64_t UnixSec(void) {
	auto now = chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

uint64_t UnixNanoSec(void) {
	auto now = chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

string AppTime(void) {
    auto now = std::chrono::high_resolution_clock::now();
	auto cost = std::chrono::duration_cast<std::chrono::milliseconds>(now - appStart).count();
	stringstream ss;
	ss.width(8);
	ss << cost << " ";
	return ss.str();
}

void ChronoTest(void) {

}