#pragma once
#include <stdlib.h>
#include <cstdlib>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Random
{
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

	inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max) {
		return glm::vec3(
			random(min.x, max.x),
			random(min.y, max.y),
			random(min.z, max.z)
		);
	}

	inline glm::vec3 randomInUnitSphere()
	{
		glm::vec3 v;
		// generate random vectors between -1 <-> +1, return vector if length is less than 1
		do
		{
			v = glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) }; //get random vector between(-1, -1, -1) and (1, 1, 1)
		} while (glm::length2(v) >= 1.0f);

		return v;
	}
};