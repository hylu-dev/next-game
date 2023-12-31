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

float3 float4x4::operator*(const float3& rhs) const {
    float3 result;
    result.x = m00 * rhs.x + m01 * rhs.y + m02 * rhs.z + m03;
    result.y = m10 * rhs.x + m11 * rhs.y + m12 * rhs.z + m13;
    result.z = m20 * rhs.x + m21 * rhs.y + m22 * rhs.z + m23;
    return result;
}

// static

float4x4 float4x4::CreateProjection(float fov, float aspectRatio, float near, float far) {
    float4x4 projectionMatrix;

    float tanHalfFov = tanf(TO_RAD(fov / 2.0f));
    float planeRange = far - near;

    projectionMatrix.m00 = 1.0f / (aspectRatio * tanHalfFov);
    projectionMatrix.m11 = 1.0f / tanHalfFov;
    projectionMatrix.m22 = -(far + near) / planeRange;
    projectionMatrix.m23 = -1.0f;
    projectionMatrix.m32 = -(2.0f * far * near) / planeRange;
    projectionMatrix.m33 = 0.0f;

    return projectionMatrix;
}

float4x4 float4x4::CreateView(float3 camera, float3 target, float3 up) {
    float4x4 viewMatrix;

    float3 forward = { target.x - camera.x, target.y - camera.y, target.z - camera.z };
    forward = { forward.x / sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z),
                forward.y / sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z),
                forward.z / sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z) };

    float3 right = { up.y * forward.z - up.z * forward.y, up.z * forward.x - up.x * forward.z, up.x * forward.y - up.y * forward.x };
    right = { right.x / sqrtf(right.x * right.x + right.y * right.y + right.z * right.z),
              right.y / sqrtf(right.x * right.x + right.y * right.y + right.z * right.z),
              right.z / sqrtf(right.x * right.x + right.y * right.y + right.z * right.z) };

    up = { forward.y * right.z - forward.z * right.y, forward.z * right.x - forward.x * right.z, forward.x * right.y - forward.y * right.x };
    up = { up.x / sqrtf(up.x * up.x + up.y * up.y + up.z * up.z),
           up.y / sqrtf(up.x * up.x + up.y * up.y + up.z * up.z),
           up.z / sqrtf(up.x * up.x + up.y * up.y + up.z * up.z) };

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