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

	// Returns the number of triangles created from clipping against a plane
	// Purpose: After projection, if a triangle is partly clipped out of view, we mustn't draw the portion of
	// the triangle outside of view. To do this, we need to create a flat edge against the plane where
	// the triangle is clipped. Depending on how many points are clipped, we need to add more triangles
	// to turn the clipped points into a flat edge (we want to avoid quads).
	static int ClipAgainstPlane(float3 planePoint, float3 planeNormal, Triangle& in, Triangle& out1, Triangle& out2);

};

