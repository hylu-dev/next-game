#pragma once

class Camera {
private:
	float4x4 matView;
	float4x4 matProj;
	float3 target = float3(0, 0, 1.0f);

	float3 forward;
	float3 up = float3(0.0f, 1.0f, 0.0f);
	float3 right;

public:
	float fov = 120.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	Transform transform;

	Camera() = default;
	Camera(float _fov, float _near, float _far) : fov(_fov), nearPlane(_near), farPlane(_far) {};

	float3 Forward() { return forward; }
	float3 Up() { return up; }
	float3 Right() { return right; }

	float4x4& GetView() { return matView; }
	
	float4x4& GetProjection() { return matProj; }

	void Initialize();

	void Update();

	void Destroy();

};