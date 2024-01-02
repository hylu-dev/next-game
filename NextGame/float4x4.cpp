#include "stdafx.h"
#include "float4x4.h"

float4x4 float4x4::Identity = float4x4();
float4x4 float4x4::Zero = float4x4(0);

// matrix to matrix

float4x4 float4x4::operator+(const float4x4& rhs) const {
    float4x4 result = float4x4::Zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m[i][j] + rhs.m[i][j];
    return result;
}

float4x4 float4x4::operator-(const float4x4& rhs) const {
    float4x4 result = float4x4::Zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m[i][j] - rhs.m[i][j];
    return result;
}

float4x4 float4x4::operator*(const float4x4& rhs) const {
    float4x4 result = float4x4::Zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.m[i][j] += m[i][k] * rhs.m[k][j];
    return result;
}

float4x4 float4x4::operator/(const float4x4& rhs) const {
    // Placeholder as we will not use this operator for matrices
    return *this;
}

// matrix to vector
// I won't use a 4x1 vector on it's own elsewhere so simplifying with a
// hacky 4x4 matrix and 3x1 vector multiplication
float3 float4x4::operator*(const float3& rhs) const {
    float3 result;
    result.x = m00 * rhs.x + m10 * rhs.y + m20 * rhs.z + m30;
    result.y = m01 * rhs.x + m11 * rhs.y + m21 * rhs.z + m31;
    result.z = m02 * rhs.x + m12 * rhs.y + m22 * rhs.z + m32;
    float w = rhs.x * m03 + rhs.y * m13 + rhs.z * m23 + m33;
    if (w != 0.0f) {
        result.x /= w;
        result.y /= w;
    }

    return result;
}

// static

float4x4 float4x4::CreateProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
    float4x4 projectionMatrix = float4x4::Zero;

    float tanHalfFov = tanf(TO_RAD(fov*0.5f));

    projectionMatrix.m00 = 1.0f / (aspectRatio * tanHalfFov);
    projectionMatrix.m11 = 1.0f / tanHalfFov;
    projectionMatrix.m22 = farPlane / (farPlane - nearPlane);
    projectionMatrix.m23 = 1.0f;
    projectionMatrix.m32 = (-farPlane * nearPlane) / (farPlane - nearPlane);
    projectionMatrix.m33 = 0.0f;

    return projectionMatrix;
}

float4x4 float4x4::CreateView(float3 camera, float3 target, float3 up) {
    float4x4 viewMatrix;
    float3 forward = target - camera;
    float3 right = up.Cross(forward);
    forward.Normalize();
    right.Normalize();
    up.Normalize();

    viewMatrix.m00 = right.x;
    viewMatrix.m01 = up.x;
    viewMatrix.m02 = -forward.x;
    viewMatrix.m03 = 0.0f;

    viewMatrix.m10 = right.y;
    viewMatrix.m11 = up.y;
    viewMatrix.m12 = -forward.y;
    viewMatrix.m13 = 0.0f;

    viewMatrix.m20 = right.z;
    viewMatrix.m21 = up.z;
    viewMatrix.m22 = -forward.z;
    viewMatrix.m23 = 0.0f;

    viewMatrix.m30 = -right.Dot(camera);
    viewMatrix.m31 = -up.Dot(camera);
    viewMatrix.m32 = forward.Dot(camera);
    viewMatrix.m33 = 1.0f;

    return viewMatrix;
}

float4x4 float4x4::CreateRotation(float angleX, float angleY, float angleZ) {
    float4x4 rotationMatrix = float4x4::Identity;
    float radX = TO_RAD(angleX);
    float radY = TO_RAD(angleY);
    float radZ = TO_RAD(angleZ);
    float cosX = cosf(radX);
    float sinX = sinf(radX);
    float cosY = cosf(radY);
    float sinY = sinf(radY);
    float cosZ = cosf(radZ);
    float sinZ = sinf(radZ);

    // Rotation matrix for X-axis
    float4x4 rotationX;
    rotationX.m11 = cosX;
    rotationX.m12 = -sinX;
    rotationX.m21 = sinX;
    rotationX.m22 = cosX;
    // Rotation matrix for Y-axis
    float4x4 rotationY;
    rotationY.m00 = cosY;
    rotationY.m02 = sinY;
    rotationY.m20 = -sinY;
    rotationY.m22 = cosY;
    // Rotation matrix for Z-axis
    float4x4 rotationZ;
    rotationZ.m00 = cosZ;
    rotationZ.m01 = -sinZ;
    rotationZ.m10 = sinZ;
    rotationZ.m11 = cosZ;

    // Combined rotation
    rotationMatrix = rotationZ * rotationY * rotationX;
    return rotationMatrix;
}

float4x4 float4x4::CreateTranslation(float3 vec) {
    float4x4 translationMatrix = float4x4::Identity;

    translationMatrix.m03 = vec.x;
    translationMatrix.m13 = vec.y;
    translationMatrix.m23 = vec.z;

    return translationMatrix;
}