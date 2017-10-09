#include <windows.h>
#include <cstdint>
#include "common.h"

bool BindCpu(int cpuidx)
{
	return SetThreadAffinityMask(GetCurrentThread(), (std::uint64_t)1 << cpuidx);
}