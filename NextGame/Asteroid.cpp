#include "stdafx.h"
#include "Asteroid.h"
#include "MeshFilter.h"
#include "AsteroidMesh.h"
#include "SphereCollider.h"
#include "ParticleEmitter.h"
#include "Scrap.h"

void Asteroid::Initialize() {
	parentEntity->GetTransform().scale *= Utils::RandomFloatUniform() + 0.5;
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(AsteroidMesh(1));
	meshFilter->SetColor({ 0.4, 0.4, 0.8 });
	SphereCollider* collider = parentEntity->AddComponent<SphereCollider>();
	collider->radius = parentEntity->GetTransform().scale.x;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Tag() == "Bullet" || c2->parentEntity->Tag() == "Ship") {
			emitter->Emit();
			SpawnScrap();
			c1->active = false;
			Scene::Get().RemoveEntity(c1->parentEntity);
			App::PlaySoundW("Assets/SoundEffects/Cracking.wav");
		}
		});
	rotateVec = {
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1)
	};
	animator = parentEntity->AddComponent<Animator>();
	emitter = parentEntity->AddComponent<ParticleEmitter>();
	emitter->burstSize = 100;
	emitter->active = false;
	emitter->size = 2;
	emitter->shape = EmissionShape::RADIAL;
	emitter->radialOffset = collider->radius;
	emitter->speed = 30.0f;
}

void Asteroid::Update() {
	parentEntity->GetTransform().rotation += rotateVec*(50.0f * Time::Get().DeltaTime());
}

void Asteroid::Destroy() {
}

void Asteroid::SpawnScrap() {
	for (int i = 0; i < parentEntity->GetTransform().scale.x; i++) {
		Entity* entity = Scene::Get().CreateEntity("Scrap");
		entity->GetTransform().position = parentEntity->GetTransform().position;
		entity->GetTransform().rotation = parentEntity->GetTransform().rotation;
		Scrap* scrap = entity->AddComponent<Scrap>();
	}
}
