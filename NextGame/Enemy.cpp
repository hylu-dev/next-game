#include "stdafx.h"
#include "Enemy.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"

void Enemy::Initialize() {
	target = Scene::Get().GetEntityByName("Player");

	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(4));
	meshFilter->SetColor(float3(1.0f, 0, 0));
	meshFilter->SetVertexShader([](float3& vertex) {
		float dist = vertex.Distance(float3(0));
		float3 displace = 0.05f * (5.0f - 5.0f * dist) * sinf(20.0f * dist - 5.0f * Time::Get().Elapsed());
		vertex += vertex*displace;
		});
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
	collider->SetCollisionHook([](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Name() == "Wall" || c2->parentEntity->Name() == "Enemy") {
			float3& p1 = c1->parentEntity->GetTransform().position;
			float3& p2 = c2->parentEntity->GetTransform().position;
			float3 direction = (p1 - p2).Normalized();
			p1 += direction * 10.0f * Time::Get().DeltaTime();
		}
		});
}

void Enemy::Update() {
	if (target != nullptr) {
		float3& p1 = parentEntity->GetTransform().position;
		float3& p2 = target->GetTransform().position;
		float3 direction = p2 - p1;
		if (direction.Length() < range) {
			p1 += direction.Normalized() * speed * Time::Get().DeltaTime();
		}
	}	
}

void Enemy::Destroy() {
}
