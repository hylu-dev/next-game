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

float3 float3::Normalized()
{
    float3 vec = *this;
    if (vec != Zero) {
        vec /= vec.Length();
    }
    return vec;
}

float float3::Dot(const float3& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

float3 float3::Cross(const float3& rhs) const {
    return float3(
        y * rhs.z - z * rhs.y,
        z * rhs.x - x * rhs.z,
        x * rhs.y - y * rhs.x
    );
}

float float3::Distance(const float3& rhs) const {
    return (*this - rhs).Length();
}

float3 float3::PointOfPlaneIntersect(float3& planePoint, float3& planeNormal, float3& lineStart, float3& lineEnd) {
    planeNormal.Normalize();
    float planeDirection = -planeNormal.Dot(planePoint);
    float ad = lineStart.Dot(planeNormal);
    float bd = lineEnd.Dot(planeNormal);
    float t = (-planeDirection - ad) / (bd - ad);
    float3 lineVector = lineEnd - lineStart;
    float3 lineIntersection = lineVector * t;
    return lineStart + lineIntersection;
}

int float3::ClipAgainstPlane(float3 planePoint, float3 planeNormal, float3& in1, float3& in2, float3& out1, float3& out2) {
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
    float3* innerPoints[2]; int innerCount = 0;
    float3* outerPoints[2]; int outerCount = 0;

    // Find distance points are from plane and store as required
    dist(in1) >= 0 ? innerPoints[innerCount++] = &in1 : outerPoints[outerCount++] = &in1;
    dist(in2) >= 0 ? innerPoints[innerCount++] = &in2 : outerPoints[outerCount++] = &in2;

    // No line in view
    if (innerCount == 0) { return 0; }

    // Full line in view, no clip
    if (innerCount == 2) {
        out1 = in1;
        out2 = in2;
        return 1;
    }

    // Two points clipped. Close the triangle against the plane
    if (innerCount == 1 && outerCount == 1) {
        out1 = *innerPoints[0];
        out2 = float3::PointOfPlaneIntersect(planePoint, planeNormal, *innerPoints[0], *outerPoints[0]);
        return 1;
    }

    return 0;
}
