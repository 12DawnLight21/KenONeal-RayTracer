#pragma once
#include <stdlib.h>
#include <cstdlib>
#include <utility>

class Random
{
public:

public:
	void seedRandom(unsigned int seed)
	{
		srand(seed);
	}

	float random01()
	{
		// cast him to a float or it doesnt work kenneth
		return static_cast<float>(std::rand()) / RAND_MAX;
	}

	float random(float min, float max)
	{
		if (min > max) {

			std::swap(min, max);
		}

		return min + (max - min) * random01();
	}
};