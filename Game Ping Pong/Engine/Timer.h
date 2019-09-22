#pragma once
#include <chrono>
#include <iostream>

// The timer class has 2 purposes: 
// 1. Test time on performance 
// 2. Count down a clock 

#define USAGE_TYPE char
#define TEST_TIME 0
#define COUNT_DOWN 1

class Timer
{
private:
	USAGE_TYPE usageType;
	union {
		const char *funcTest; // in case using of test_time
		float* countDown; // incase using of count_down (units of seconds)
	};

	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<float> duration;

public:
	// Constructor in case usageType of test_time
	Timer(const char* funcTest) :
		funcTest(funcTest),
		usageType(TEST_TIME)
	{}

	// Constructor in case usageType of count_down
	Timer(float &time_count_down) :
		countDown(&time_count_down),
		usageType(COUNT_DOWN)
	{}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		switch (usageType)
		{
			case TEST_TIME:
				std::cout << funcTest << " took " << duration.count() * 1000.0f << " ms" << std::endl;
				break;
			case COUNT_DOWN:
				*countDown -= duration.count();
				break;
		}
	}
};



