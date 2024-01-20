#pragma once
#include "Component.h"
#include "Animator.h"
#include "ParticleEmitter.h"

class DarkStar : public Component {
	Entity* target = nullptr;
	Animator* animator = nullptr;
	ParticleEmitter* emitter = nullptr;

	float shaderStability = 0.02f;
	float shaderSpeed = 5.0f;

	bool isPressed = false;

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};