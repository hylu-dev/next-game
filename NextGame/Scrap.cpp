#include "stdafx.h"
#include "Scrap.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "SphereCollider.h"
#include "ParticleEmitter.h"
#include "Animator.h"

void Scrap::Initialize() {
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(1));
	meshFilter->SetColor(float3({1, 1, 0}));
	SphereCollider* collider = parentEntity->AddComponent<SphereCollider>();
	collider->radius = parentEntity->GetTransform().scale.x + pickUpOffset;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Tag() == "Ship") {
			float3 direction = c2->parentEntity->GetTransform().position - c1->parentEntity->GetTransform().position;
			float distance = direction.Length();
			parentEntity->GetTransform().position += direction * (10.0f * Time::Get().DeltaTime());
		}
	});
	Animator* animator = parentEntity->AddComponent<Animator>();
	animator->Animate(
		parentEntity->GetTransform().position,
		parentEntity->GetTransform().position + float3({
			Utils::RandomFloat(-spawnRadius, spawnRadius),
			Utils::RandomFloat(-spawnRadius, spawnRadius),
			Utils::RandomFloat(-spawnRadius, spawnRadius)
			}),
		0.3f,
		new EaseOut()
	);
}

void Scrap::Update() {
}

void Scrap::Destroy() {
}
