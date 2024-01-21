#include "stdafx.h"
#include "Camera.h"

void Camera::Initialize() {
	target += transform.position;
	matView = float4x4::CreateView(
		transform.position,
		target,
		up
	);

	matProj = float4x4::CreateProjection(
		fov,
		APP_VIRTUAL_WIDTH / APP_VIRTUAL_HEIGHT,
		nearPlane,
		farPlane
	);
}

void Camera::Update() {
	forward = transform.Forward();
	target = transform.position + forward;
	matView = float4x4::CreateView(
		transform.position,
		target,
		float3(0, 1.0f, 0)
	);
	up = float3(0.0f, 1.0f, 0.0f);
	up = up - forward * up.Dot(forward);
	up.Normalize();
	right = up.Cross(forward).Normalized();
}

void Camera::Destroy() {
}
