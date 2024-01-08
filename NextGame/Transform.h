#pragma once

#include "float3.h"

struct Transform {
	float3 position;
	float3 rotation;
	float3 scale = float3::One;

	Transform() = default;
	Transform(float3 _position, float3 _rotation, float3 _scale) : position(_position), rotation(_rotation), scale(_scale) {};
};