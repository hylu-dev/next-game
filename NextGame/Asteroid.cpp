#include "stdafx.h"
#include "Asteroid.h"
#include "MeshFilter.h"
#include "AsteroidMesh.h"
#include "SphereCollider.h"
#include "ParticleEmitter.h"
#include "Scrap.h"

void Asteroid::Initialize() {
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(AsteroidMesh(3));
	meshFilter->SetColor(float3(0.5f));
	SphereCollider* collider = parentEntity->AddComponent<SphereCollider>();
	collider->radius = parentEntity->GetTransform().scale.x;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Name() == "Bullet" || c2->parentEntity->Tag() == "Ship") {
			emitter->Emit();
			SpawnScrap();
			Scene::Get().RemoveEntity(c1->parentEntity);
		}
		});
	rotateVec = {
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1)
	};

	emitter = parentEntity->AddComponent<ParticleEmitter>();
	emitter->burstSize = 100;
	emitter->active = false;
	emitter->size = 2;
	emitter->color = float3(0.5f);
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
	for (int i = 0; i < 10; i++) {
		Entity* entity = Scene::Get().CreateEntity("Scrap");
		entity->GetTransform().position = parentEntity->GetTransform().position;
		entity->GetTransform().rotation = parentEntity->GetTransform().rotation;
		Scrap* scrap = entity->AddComponent<Scrap>();
	}
}
