#include "stdafx.h"
#include "ShipA.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "TimingFunction.h"
#include "Bullet.h"

void ShipA::Initialize() {
	// Ship Components
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
	animator = parentEntity->AddComponent<Animator>();

	trailEmitter = parentEntity->AddComponent<ParticleEmitter>();
	trailEmitter->burstSize = 5;
	trailEmitter->active = false;
	trailEmitter->size = 0.5f;
	trailEmitter->color = float3(1.0f, 0.5f, 0.2f);
	trailEmitter->shape = EmissionShape::CONE;
	trailEmitter->speed = 10.0f;
	trailEmitter->coneWidth = 20.0f;

	bulletEmitter = parentEntity->AddComponent<ParticleEmitter>();
	bulletEmitter->burstSize = 50;
	bulletEmitter->size = 2;
	bulletEmitter->active = false;
	bulletEmitter->color = { 1,0,0 };
	bulletEmitter->speed = 50.0f;
	bulletEmitter->coneWidth = 30.0f;
	bulletEmitter->shape = EmissionShape::CONE;
	bulletEmitter->direction = parentEntity->GetTransform().rotation;
	// Member Variables
	camera = Scene::Get().GetCamera();
}

void ShipA::Update() {
	trailEmitter->direction = camera->Forward() * -1;
	trailEmitter->Emit();

	if (active) {
		this->MovementHandler();
		this->FireWeapon();
	}
}

void ShipA::Destroy() {
	animator = nullptr;
	trailEmitter = nullptr;
	bulletEmitter = nullptr;
}

void ShipA::MovementHandler() {
	float3& position = parentEntity->GetTransform().position;
	float3& rotation = parentEntity->GetTransform().rotation;
	float3& scale = parentEntity->GetTransform().scale;
	float velocity = speed * Time::Get().DeltaTime();

	float deltaAcceleration = acceleration * Time::Get().DeltaTime();
	float deltaFriction = 1.0 - friction * Time::Get().DeltaTime();

	if (rotationSpeed.Length() <= speed) {
		if (App::IsKeyPressed('A')) {
			rotationSpeed += camera->Up()*deltaAcceleration;
		}
		if (App::IsKeyPressed('D')) {
			rotationSpeed -= camera->Up() *deltaAcceleration;
		}
		if (App::IsKeyPressed(VK_SPACE)) {
			rotationSpeed.x += deltaAcceleration;
		}
		if (App::IsKeyPressed(VK_LSHIFT)) {
			rotationSpeed.x -= deltaAcceleration;
		}
	}
	
	if (movement.Length() <= speed) {
		if (App::IsKeyPressed('W')) {
			movement += camera->Forward() * deltaAcceleration;
		}
		if (App::IsKeyPressed('S')) {
			movement -= camera->Forward() * deltaAcceleration;
		}
	}

	Time::Get().testFloat3 = rotation;

	position += movement *= deltaFriction;
	rotation += rotationSpeed *= deltaFriction;

	camera->transform.rotation = rotation;
	camera->transform.position = GetOffsetCamera();

}

void ShipA::FireWeapon() {
	if (!App::IsKeyPressed('F') || !bulletLoaded) { return; }
	bulletLoaded = false;
	for (int i = 0; i < multishot; i++) {
		Entity* entity = Scene::Get().CreateEntity("Bullet");
		entity->GetTransform().position = parentEntity->GetTransform().position;
		entity->GetTransform().rotation = parentEntity->GetTransform().rotation;
		Bullet* bullet = entity->AddComponent<Bullet>();
		bullet->forward = camera->Forward();
		bulletEmitter->direction = camera->Forward();
		bulletEmitter->Emit();
	}
}

float3 ShipA::GetOffsetCamera() {
	return parentEntity->GetTransform().position + camera->Forward() * cameraXOffset + camera->Up() * cameraYOffset;
}
