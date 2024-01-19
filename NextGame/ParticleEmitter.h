#pragma once
#include "Component.h"

enum EmissionShape {
	RADIAL,
	CONE,
};

class ParticleEmitter : public Component {
private:
	float timer = 0.0f;

public:
	// Emission
	EmissionShape shape = RADIAL;
	float frequency = 0.1f;
	float coneWidth = 30; // DEGREES
	short burstSize = 1;

	// Particle
	float size = 1.0f;
	float speed = 10.0f;
	float lifetime = 1.0f;
	float3 color = float3::One;
	float3 direction = float3(0, 1.0f, 0);
	bool fade = true;
	bool rotate = true;


public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;
};

