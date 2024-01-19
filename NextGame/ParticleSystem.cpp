#include "stdafx.h"
#include "ParticleSystem.h"
#include "Entity.h"
#include "Particle.h"

ParticleSystem* ParticleSystem::instance = nullptr;

void ParticleSystem::Initialize() {

}

void ParticleSystem::Update() {
	for (auto& part : particles) {
		part->Update();
	}

	for (auto& part : particlesToDelete) {
		particles.remove(part);
		part->Destroy();
		delete part;
		part = nullptr;
	}
	particlesToDelete.clear();
}

void ParticleSystem::Destroy() {
	particles.clear();
	particlesToDelete.clear();
	delete instance;
}

Particle* ParticleSystem::CreateParticle(float3 position) {
	Entity* entity = new Entity();
	entity->GetTransform().position = position;
	Particle* part = entity->AddComponent<Particle>();
	particles.push_back(entity);
	return part;
}

void ParticleSystem::RemoveParticle(Entity* part) {
	particlesToDelete.push_back(part);
}
