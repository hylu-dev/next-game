#pragma once
#include "ObservableComponent.h"
#include "Animator.h"
#include "ParticleEmitter.h"
#include "SphereCollider.h"
#include "MeshFilter.h"

class DarkStar : public ObservableComponent {
	Entity* target = nullptr;
	Animator* animator = nullptr;
	MeshFilter* meshFilter = nullptr;
	ParticleEmitter* pulseEmitter = nullptr;
	ParticleEmitter* constantEmitter = nullptr;
	SphereCollider* collider = nullptr;

	float3 color = { 1,0,1 };

	float shaderStability = 0.02f;
	float shaderSpeed = 5.0f;

	bool isPressed = false;

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};