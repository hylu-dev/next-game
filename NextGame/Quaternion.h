#pragma once
union Quaternion {
	struct {
		float w, x, y, z;
	};
	float vec[4];

    Quaternion() : w(0), x(0), y(0), z(0) {};

    Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {};

    void Normalize();

    void RotateVector(float3& vec) ;

    Quaternion GetConjugate();

    Quaternion operator*(const Quaternion& q);

    static Quaternion fromEulerAngles(float3 angles);
};

