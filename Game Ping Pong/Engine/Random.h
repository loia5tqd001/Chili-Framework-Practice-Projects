#pragma once
#include <random>

// 2 ways of usage:

// 1.
// int random_numbers[n];
// auto dist = Random::Distribute(min, max);
// for (int i = 0; i < n; i++)
// {
// 	random_numbers[i] = dist( Random::RNG() );
// }

// 2.
// int random_numbers[n];
// for (int i = 0; i < n; i++)
// {
// 	random_numbers[i] = Random::Next(min, max);
// }

class Random
{
private:
	std::random_device rd;
	std::mt19937 rng = std::mt19937(rd());
	Random() = default;


public:
	// for 1. purpose
	static std::mt19937& RNG()
	{
		static Random instance;
		return instance.rng;
	}
	// 1.
	static std::uniform_int_distribution<int> Distribute(int min, int max)
	{
		return std::uniform_int_distribution<int>(min, max);
	}

	// for 2. purpose
	static int Next(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(RNG());
	}
};



