#pragma once

#include <list>
#include "Particle.h"
#include "ParticleEmitter.h"

class Particle;

class ParticleSystem {
private:
	friend ParticleEmitter;
	friend Particle;

	std::list<Entity*> particles;
	std::list<Entity*> particlesToDelete;

	static ParticleSystem* instance;

public:
	static ParticleSystem& Get() {
		if (instance == nullptr) {
			instance = new ParticleSystem();
		}
		return *instance;
	}

	void Initialize();

	void Update();

	void Destroy();

private:
	ParticleSystem() = default;
	ParticleSystem Renderer(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

	Particle* CreateParticle(float3 position);

	void RemoveParticle(Entity* part);
};