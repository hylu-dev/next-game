#pragma once
#include "Component.h"
#include "ParticleEmitter.h"

class Asteroid :public Component {
	float3 rotateVec;
	ParticleEmitter* emitter = nullptr;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void SpawnScrap();
};

