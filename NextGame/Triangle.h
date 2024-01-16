#pragma once

#include "float3.h"

union Triangle
{
	struct {
		float3 p0;
		float3 p1;
		float3 p2;
		float3 color;
	};

	float3 p[4];

	Triangle() : p0(0), p1(0), p2(0), color(float3::One) {};
	Triangle(const float3& _p0, const float3& _p1, const float3& _p2) : p0(_p0), p1(_p1), p2(_p2), color(float3::One) {}

	void Draw();

	Triangle operator+(const Triangle rhs) const;
	Triangle operator-(const Triangle rhs) const;
	Triangle operator*(const Triangle rhs) const;
	Triangle operator/(const Triangle rhs) const;

	Triangle operator+(const float3 rhs) const;
	Triangle operator-(const float3 rhs) const;
	Triangle operator*(const float3 rhs) const;
	Triangle operator/(const float3 rhs) const;

	void ApplyMatrix(float4x4 matrix);

	void Normalize();

	float3 CalcNormal();

};

