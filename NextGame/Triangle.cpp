#include "stdafx.h"
#include "Triangle.h"

void Triangle::Draw() {
	App::DrawLine(
		p0.x, p0.y,
		p1.x, p1.y,
		color.x, color.y, color.z
	);
	App::DrawLine(
		p1.x, p1.y,
		p2.x, p2.y,
		color.x, color.y, color.z
	);
	App::DrawLine(
		p2.x, p2.y,
		p0.x, p0.y,
		color.x, color.y, color.z
	);
}

Triangle Triangle::operator+(const Triangle rhs) const
{
	return Triangle(p0+rhs.p0, p1 + rhs.p1, p2 + rhs.p2);
}

Triangle Triangle::operator-(const Triangle rhs) const
{
	return Triangle(p0 - rhs.p0, p1 - rhs.p1, p2 - rhs.p2);
}

Triangle Triangle::operator*(const Triangle rhs) const
{
	return Triangle(p0 * rhs.p0, p1 * rhs.p1, p2 * rhs.p2);
}

Triangle Triangle::operator/(const Triangle rhs) const
{
	return Triangle(p0 / rhs.p0, p1 / rhs.p1, p2 / rhs.p2);
}

Triangle Triangle::operator+(const float3 rhs) const
{
	return Triangle(p0 + rhs, p1 + rhs, p2 + rhs);
}

Triangle Triangle::operator-(const float3 rhs) const
{
	return Triangle(p0 - rhs, p1 - rhs, p2 - rhs);
}

Triangle Triangle::operator*(const float3 rhs) const
{
	return Triangle(p0 * rhs, p1 * rhs, p2 * rhs);
}

Triangle Triangle::operator/(const float3 rhs) const
{
	if (rhs != float3::Zero) {
		return Triangle(p0 / rhs, p1 / rhs, p2 / rhs);
	}
	return *this;
}

void Triangle::ApplyMatrix(float4x4 matrix) {
	p0 = matrix * p0;
	p1 = matrix * p1;
	p2 = matrix * p2;
}

void Triangle::Normalize() {
	p0.Normalize();
	p1.Normalize();
	p2.Normalize();
}

float3 Triangle::CalcNormal()
{
	return (p1 - p0).Cross(p2 - p1);
}

int Triangle::ClipAgainstPlane(float3 planePoint, float3 planeNormal, Triangle& in, Triangle& out1, Triangle& out2) {
	planeNormal.Normalize();

	auto dist = [&](float3& point) {
		float3 n = point.Normalized();
		return (
			planeNormal.x * point.x +
			planeNormal.y * point.y +
			planeNormal.z * point.z -
			planeNormal.Dot(planePoint)
			);
		};

	// Arrays to store points on either side of plane
	float3* innerPoints[3]; int innerCount = 0;
	float3* outerPoints[3]; int outerCount = 0;
	// Find distance points are from plane and store as required
	dist(in.p0) >= 0 ? innerPoints[innerCount++] = &in.p0 : outerPoints[outerCount++] = &in.p0;
	dist(in.p1) >= 0 ? innerPoints[innerCount++] = &in.p1 : outerPoints[outerCount++] = &in.p1;
	dist(in.p2) >= 0 ? innerPoints[innerCount++] = &in.p2 : outerPoints[outerCount++] = &in.p2;

	// The following conditions will cover all possible clipping cases for a triangles

	// No triangle in view
	if (innerCount == 0) { return 0; }

	// Full triangle in view, no clip
	if (innerCount == 3) {
		out1 = in;
		return 1; 
	}

	// Two points clipped. Close the triangle against the plane
	if (innerCount == 1 && outerCount == 2) {
		out1.p0 = *innerPoints[0];
		out1.p1 = float3::PointOfPlaneIntersect(planePoint, planeNormal, *innerPoints[0], *outerPoints[0]);
		out1.p2 = float3::PointOfPlaneIntersect(planePoint, planeNormal, *innerPoints[0], *outerPoints[1]);
		return 1;
	}
	// One point clipped, we create a quad with two new triangles
	if (innerCount == 2 && outerCount == 1) {
		out1.p0 = *innerPoints[0];
		out1.p1 = *innerPoints[1];
		out1.p2 = float3::PointOfPlaneIntersect(planePoint, planeNormal, *innerPoints[0], *outerPoints[0]);

		out2.p0 = *innerPoints[1];
		out2.p1 = out1.p2;
		out2.p2 = float3::PointOfPlaneIntersect(planePoint, planeNormal, *innerPoints[1], *outerPoints[0]);
		return 2;
	}

	return 0;
}
