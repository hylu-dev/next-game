#include "stdafx.h"
#include "Quaternion.h"

void Quaternion::Normalize() {
    float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

void Quaternion::RotateVector(float3& vec) {
    Quaternion vectorQuat(0, vec.x, vec.y, vec.z);
    Quaternion conjugate = this->GetConjugate();
    Quaternion rotatedVector = *this * vectorQuat * conjugate;
    vec.x = rotatedVector.x;
    vec.y = rotatedVector.y;
    vec.z = rotatedVector.z;
}

Quaternion Quaternion::GetConjugate() {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::operator*(const Quaternion& q) {
    float _w = w * q.w - x * q.x - y * q.y - z * q.z;
    float _x = w * q.x + x * q.w + y * q.z - z * q.y;
    float _y = w * q.y - x * q.z + y * q.w + z * q.x;
    float _z = w * q.z + x * q.y - y * q.x + z * q.w;

    return Quaternion(_w, _x, _y, _z);
}

Quaternion Quaternion::fromEulerAngles(float3 angles) {
    // Convert Euler angles to radians
    float halfPitch = TO_RAD(-angles.y) * 0.5f;
    float halfYaw = TO_RAD(angles.z) * 0.5f;
    float halfRoll = TO_RAD(-angles.x) * 0.5f;

    // Calculate sine and cosine values
    float sinPitch = std::sin(halfPitch);
    float cosPitch = std::cos(halfPitch);
    float sinYaw = std::sin(halfYaw);
    float cosYaw = std::cos(halfYaw);
    float sinRoll = std::sin(halfRoll);
    float cosRoll = std::cos(halfRoll);

    // Calculate quaternion components
    float qw = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
    float qx = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    float qy = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    float qz = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;

    return Quaternion(qw, qx, qy, qz);
}