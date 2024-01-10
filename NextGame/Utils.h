#pragma once

#include <random>

namespace Utils {
	extern std::random_device rd;
	extern std::mt19937 gen;
	extern std::uniform_real_distribution<float> dis;

	float RandomFloatUniform();

	float RandomFloat(float min, float max);

	float Clamp(float value, float minVal, float maxVal);

}