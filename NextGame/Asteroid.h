#pragma once
#include "Component.h"
#include "ParticleEmitter.h"
#include "Animator.h"

class Asteroid :public Component {
public:
	float3 rotateVec;
	ParticleEmitter* emitter = nullptr;
	Animator* animator = nullptr;


	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void SpawnScrap();
};

