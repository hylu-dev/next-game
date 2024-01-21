#pragma once
#include "ObservableComponent.h"
#include "Animator.h"
#include "ParticleEmitter.h"
#include "SphereCollider.h"
#include "MeshFilter.h"
#include "Asteroid.h"

class DarkStar : public ObservableComponent {
public:
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
	int health = 6;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void SpawnAsteroids();

	void Pulse();

	void PullOrbits();

	void Supernova();
};