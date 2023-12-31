#include "stdafx.h"
#include "float3.h"

float3 float3::Zero = float3(0);
float3 float3::One = float3(1);

float3 float3::operator+(const float3 rhs) const {
    return float3(x + rhs.x, y + rhs.y, z + rhs.z);
}

float3 float3::operator-(const float3 rhs) const {
    return float3(x - rhs.x, y - rhs.y, z - rhs.z);
}

float3 float3::operator*(const float3 rhs) const {
    return float3(x * rhs.x, y * rhs.y, z * rhs.z);
}

float3 float3::operator/(const float3 rhs) const {
    if (rhs.x != 0.0f && rhs.y != 0.0f && rhs.z != 0.0f) {
        return float3(x / rhs.x, y / rhs.y, z / rhs.z);
    }
    else {
        return float3::Zero;
    }
}

float3& float3::operator+=(const float3 rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

float3& float3::operator-=(const float3 rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

float3& float3::operator*=(const float3 rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

float3& float3::operator/=(const float3 rhs) {
    if (rhs.x != 0.0f && rhs.y != 0.0f && rhs.z != 0.0f) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
    }
    else {
        return float3::Zero;
    }
    return *this;
}

bool float3::operator==(const float3 rhs) const {
    return (std::abs(x - rhs.x) < F_EPSILON) &&
        (std::abs(y - rhs.y) < F_EPSILON) &&
        (std::abs(z - rhs.z) < F_EPSILON);
}

bool float3::operator!=(const float3 rhs) const {
    return !(*this == rhs);
}

float3 float3::Abs() const
{
    return { std::abs(x), std::abs(y), std::abs(z) };
}

float float3::Length() const {
    return std::sqrtf(x * x + y * y + z * z);
}

float float3::LengthSquared() const {
    return x * x + y * y + z * z;
}

void float3::Normalize() {
    if (*this != Zero) {
        *this /= this->Length();
    }
}

float float3::Dot(const float3& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

float float3::Distance(const float3& rhs) const {
    return (*this - rhs).Length();
}