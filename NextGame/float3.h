#pragma once

// Technically a float4 but the fourth component will only be used for matrix math
// Operators treat it as a vector3 with the fourth component set to 1.0;
union float3 {
	struct {
		float x, y, z, w;
	};
	float vec[4];

	float3() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};
	float3(float val) : x(val), y(val), z(val), w(1.0f) {};
	float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {};
	static float3 Zero;
	static float3 One;

	float3 operator+(const float3 rhs) const;
	float3 operator-(const float3 rhs) const;
	float3 operator*(const float3 rhs) const;
	float3 operator/(const float3 rhs) const;

	float3& operator+=(const float3 rhs);
	float3& operator-=(const float3 rhs);
	float3& operator*=(const float3 rhs);
	float3& operator/=(const float3 rhs);

	bool operator==(const float3 rhs) const;
	bool operator!=(const float3 rhs) const;

	float3 Abs() const;
	float Length() const;
	float LengthSquared() const;
	void Normalize();
	float3 Normalized();
	float Dot(const float3& rhs) const;
	float3 Cross(const float3& rhs) const;
	float Distance(const float3& rhs) const;

	// The point where a line intersect a plane
	static float3 PointOfPlaneIntersect(float3& planePoint, float3& planeNormal, float3& lineStart, float3& lineEnd);

	// Look at the version in Triangle.h, same idea but with a line instead of a tri
	static int float3::ClipAgainstPlane(float3 planePoint, float3 planeNormal, float3& in1, float3& in2, float3& out1, float3& out2);
};
