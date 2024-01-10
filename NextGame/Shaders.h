#pragma once

#include "stdafx.h"
#include <functional>

namespace Shader {
	std::function<void(float3&)> CenterWave() {
		return [](float3& vertex) {
			float height = vertex.y;
			height += 10.0f * sinf(vertex.Distance(float3(0, 0, 0)) * 10.0f);
			vertex.y += height;
		};
	}
};

