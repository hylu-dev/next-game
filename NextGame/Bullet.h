#pragma once
#include "Component.h"
#include "ParticleEmitter.h"

class Bullet : public Component {
public:
	float3 color = { 1,0,0 };
	float3 forward;
	float speed = 5.0f;

	ParticleEmitter* emitter = nullptr;

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};

