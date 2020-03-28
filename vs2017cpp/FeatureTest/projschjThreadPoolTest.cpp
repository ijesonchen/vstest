
#include <iostream>
#include <vector>
#include <chrono>

#include "projschjThreadPool.h"


void projschjThreadPoolTest(void)
{
	ThreadPool pool(4);
	std::vector< std::future<int> > results;
	/*
	warning STL4014: std::result_of and std::result_of_t are deprecated in C++17
	for (int i = 0; i < 8; ++i) {
		results.emplace_back(
			pool.enqueue([i] {
			std::cout << "hello " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "world " << i << std::endl;
			return i*i;
		})
		);
	}
	*/
	for (auto && result : results)
		std::cout << result.get() << ' ';
	std::cout << std::endl;

}