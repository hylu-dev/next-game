#pragma once

union float4x4 {
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
	float m[4][4];

	float4x4() : m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
		m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
		m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
		m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f) {}

	float4x4(float val) : m00(val), m01(val), m02(val), m03(val),
		m10(val), m11(val), m12(val), m13(val),
		m20(val), m21(val), m22(val), m23(val),
		m30(val), m31(val), m32(val), m33(val) {}

	float4x4 operator+(const float4x4& rhs) const;
	float4x4 operator-(const float4x4& rhs) const;
	float4x4 operator*(const float4x4& rhs) const;
	float4x4 operator/(const float4x4& rhs) const;

	float4x4 operator*=(const float4x4& rhs);

	float3 operator*(const float3& rhs) const;

	static float4x4 CreateProjection(float fov, float aspectRatio, float near, float far);
	static float4x4 CreateView(float3 camera, float3 target, float3 up);
	static float4x4 CreateRotation(float3 vec);
	static float4x4 CreateTranslation(float3 vec);
	static float4x4 CreateScale(float3 vec);

	static float4x4 Identity;
	static float4x4 Zero;
};
