#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <ctime>

#pragma warning(disable: 4267 4244 4018 4800)

void CHECK(bool b);
std::vector<std::int64_t> ReadInt(const std::string& filename);
void SleepMs(int millisec);
void SleepSec(int sec);