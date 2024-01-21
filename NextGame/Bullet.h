#pragma once
#include "Component.h"
#include "ParticleEmitter.h"

class Bullet : public Component {
public:
	float3 color = float3::One;
	float3 forward;
	float speed = 5.0f;
	std::string targetName = "";

	ParticleEmitter* emitter = nullptr;

	void SetTarget(std::string name) { targetName = name; }

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};

