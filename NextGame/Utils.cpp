#include "stdafx.h"
#include "Utils.h"

namespace Utils {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    float randomFloatUniform() {
        return dis(gen);
    }

    float randomFloat(float min, float max) {
        return min + (max - min) * dis(gen);
    }
}