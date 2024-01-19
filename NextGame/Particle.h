#pragma once

#include "Renderable.h"
#include "ParticleEmitter.h"

class Particle : public Renderable {
private:
	friend ParticleEmitter;

	float speed = 10.0f;
	float size = 1.0f;
	float lifetime = 1.0f;
	float3 color;
	float3 direction;

	float rotationSpeed = 50.0f;
	float3 rotationDirection;

	bool fade = true;
	bool rotate = true;
	float timer = 0.0f;

	float3 p1;
	float3 p2;
	float4x4 matScale;
	float4x4 matRotate;
	float4x4 matTranslate;

public:
	void Initialize();

	void PostInitialize();
	
	void Update();

	void Destroy();

	void Render() override;
};

