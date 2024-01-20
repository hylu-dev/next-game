#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"

void ParticleEmitter::Initialize() {

}

void ParticleEmitter::Update() {
	if (!active) { return; }
	timer += Time::Get().DeltaTime();
	if (timer >= frequency) {
		timer = 0;
		this->Emit();
	}
}

void ParticleEmitter::Destroy() {

}


void ParticleEmitter::Emit() {
	for (int i = 0; i < burstSize; i++) {
		float3 _direction = direction;
		float3 spawnPosition = parentEntity->GetTransform().position;

		if (shape == EmissionShape::RADIAL) {
			_direction = float3(
				Utils::RandomFloat(-1, 1),
				Utils::RandomFloat(-1, 1),
				Utils::RandomFloat(-1, 1)
			).Normalized();
			spawnPosition += _direction * radialOffset;
		}
		else if (shape == EmissionShape::CONE) {
			float range = tanf(TO_RAD(coneWidth) * 0.5f);
			_direction += float3(
				Utils::RandomFloat(-range, range),
				Utils::RandomFloat(-range, range),
				Utils::RandomFloat(-range, range)
			);
			_direction.Normalize();
		}

		Particle* part = ParticleSystem::Get().CreateParticle(spawnPosition);
		part->size = size;
		part->speed = speed;
		part->lifetime = lifetime;
		part->color = color;
		part->direction = _direction;
		part->fade = fade;
		part->rotate = rotate;
		part->PostInitialize();
	}
}