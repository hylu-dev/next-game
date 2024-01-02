#pragma once

union float3 {
	struct {
		float x, y, z;
	};
	float vec[3];

	float3() : x(0), y(0), z(0) {};
	float3(float val) : x(val), y(val), z(val) {};
	float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
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
	float Dot(const float3& rhs) const;
	float3 Cross(const float3& rhs) const;

	float Distance(const float3& rhs) const;
};
