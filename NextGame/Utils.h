#pragma once

#include <random>

namespace Utils {
	extern std::random_device rd;
	extern std::mt19937 gen;
	extern std::uniform_real_distribution<float> dis;

	float RandomFloatUniform();

	float RandomFloat(float min, float max);

	template <typename T>
	T RandomInRange(T min, T max) {
		return min + (max - min) * dis(gen);
	}

	float Clamp(float value, float minVal, float maxVal);

	float Logistic(float value, float approachRate = 1);

	bool IsInRange(float value, float minVal, float maxVal);

}