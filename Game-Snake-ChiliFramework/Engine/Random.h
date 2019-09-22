#pragma once
#include <random>


class Random
{
private:
	std::random_device rd;
	std::mt19937 rng = std::mt19937(rd());
	Random() = default;

public:
	static std::mt19937& GetRng()
	{
		static Random instance;
		return instance.rng;
	}

	static int Next(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(GetRng());
	}

	static double NextDouble(double min, double max)
	{
		std::uniform_real_distribution<double> dist(min, max);
		return dist(GetRng());
	}
};




