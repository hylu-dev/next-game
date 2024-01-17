#include "stdafx.h"
#include "PlayerController.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"

void PlayerController::Initialize() {
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(4));
	meshFilter->SetColor(float3(0, 1, 0));
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
	collider->SetCollisionHook([](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Name() == "EnemyBox") {
			Scene::Get().RemoveEntity(c2->parentEntity);
		}
		else if (c2->parentEntity->Name() == "Wall") {
			float3& p1 = c1->parentEntity->GetTransform().position;
			float3& p2 = c2->parentEntity->GetTransform().position;
			float3 direction = (p1 - p2).Normalized();
			p1 += direction * 10.0f * Time::Get().DeltaTime();
		}
		});
}

void PlayerController::Update() {
	float3& position = parentEntity->GetTransform().position;
	float speed = 50.0f * Time::Get().DeltaTime();

	if (App::IsKeyPressed(VK_LSHIFT)) {
		speed *= 2;
	}

	if (App::IsKeyPressed('F')) {
		position.x -= speed;
	}
	if (App::IsKeyPressed('H')) {
		position.x += speed;
	}
	if (App::IsKeyPressed('T')) {
		position.y += speed;
	}
	if (App::IsKeyPressed('G')) {
		position.y -= speed;
	}
}

void PlayerController::Destroy() {
}
