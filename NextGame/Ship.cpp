#include "stdafx.h"
#include "Ship.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "TimingFunction.h"
#include "Bullet.h"
#include "Animator.h"

void Ship::Initialize() {
	parentEntity->Tag() = "Ship";
	// Ship Components
	animator = parentEntity->AddComponent<Animator>();
	meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(4));
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		float3& p1 = c1->parentEntity->GetTransform().position;
		float3& p2 = c2->parentEntity->GetTransform().position;
		if (c2->parentEntity->Name() == "AsteroidObject") {
			health -= 10;
		}
		if (c2->parentEntity->Name() == "DarkStar") {
			health -= 10;
			float3 direction = (p1 - p2).Normalized();
			p1 += direction * 20.0f * Time::Get().DeltaTime();
			animator->Animate(
				parentEntity->GetTransform().position,
				parentEntity->GetTransform().position + direction * 30.0f,
				1.0f, new EaseOut);
		}
		if (c2->parentEntity->Name() == "Scrap") {
			if (p1.Distance(p2) < 5.0f) {
				scrap += 10.0f;
				Scene::Get().RemoveEntity(c2->parentEntity);
			}
		}
		});
	animator = parentEntity->AddComponent<Animator>();

	trailEmitter = parentEntity->AddComponent<ParticleEmitter>();
	trailEmitter->burstSize = 10;
	trailEmitter->active = false;
	trailEmitter->size = 0.5f;
	trailEmitter->lifetime = 0.5f;
	trailEmitter->color = float3(1.0f, 0.5f, 0.2f);
	trailEmitter->shape = EmissionShape::CONE;
	trailEmitter->speed = 10.0f;
	trailEmitter->coneWidth = 90.0f;

	bulletEmitter = parentEntity->AddComponent<ParticleEmitter>();
	bulletEmitter->burstSize = 50;
	bulletEmitter->size = 2;
	bulletEmitter->active = false;
	bulletEmitter->color = { 1,0,1 };
	bulletEmitter->speed = 50.0f;
	bulletEmitter->coneWidth = 30.0f;
	bulletEmitter->shape = EmissionShape::CONE;
	bulletEmitter->direction = parentEntity->GetTransform().rotation;
	// Member Variables
	camera = Scene::Get().GetCamera();
}

void Ship::Update() {
	trailEmitter->direction = camera->Forward() * -1;

	if (active) {
		this->MovementHandler();
		this->FireWeapon();
	}
}

void Ship::Destroy() {
	animator = nullptr;
	trailEmitter = nullptr;
	bulletEmitter = nullptr;
}

void Ship::MovementHandler() {
	float3& position = parentEntity->GetTransform().position;
	float3& rotation = parentEntity->GetTransform().rotation;
	float3& scale = parentEntity->GetTransform().scale;
	float velocity = speed * Time::Get().DeltaTime();

	float deltaAcceleration = acceleration * Time::Get().DeltaTime();
	float deltaFriction = 1.0 - friction * Time::Get().DeltaTime();

	if (rotationSpeed.Length() <= speed) {
		if (App::IsKeyPressed('A')) {
			rotationSpeed += float3(0,1,0)*deltaAcceleration;
		}
		if (App::IsKeyPressed('D')) {
			rotationSpeed -= float3(0, 1, 0)*deltaAcceleration;
		}
		if (App::IsKeyPressed(VK_SPACE)) {
			rotationSpeed.x += deltaAcceleration;
		}
		if (App::IsKeyPressed(VK_LSHIFT)) {
			rotationSpeed.x -= deltaAcceleration;
		}
	}
	
	if (movement.Length() <= speed && fuel > 0) {
		if (App::IsKeyPressed('W')) {
			trailEmitter->Emit();
			fuel -= fuelDrain * Time::Get().DeltaTime();
			movement += forward * deltaAcceleration;
		}
		else if (App::IsKeyPressed('S')) {
			trailEmitter->Emit();
			fuel -= fuelDrain * Time::Get().DeltaTime();
			movement -= forward * deltaAcceleration;
		}
	}

	position += movement *= deltaFriction;

	// Some rendering issues with >= |90|deg x-rotations, slow down rotation and clamp near these values
	// Actually, it kinda feels better this way!
	float distanceFromMaxRotation = 90 - std::abs(rotation.x);
	rotationSpeed *= Utils::Logistic(distanceFromMaxRotation, 0.1);
	rotation += rotationSpeed *= deltaFriction;
	rotation.x = Utils::Clamp(rotation.x, -89, 89);
	Time::Get().testFloat = rotationSpeed.x;

	camera->transform.rotation = rotation;
	camera->transform.position = GetOffsetCamera();
	forward = parentEntity->GetTransform().Forward();
}

void Ship::FireWeapon() {
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

float3 Ship::GetOffsetCamera() {
	return parentEntity->GetTransform().position + forward * cameraZOffset + camera->Up() * cameraYOffset;
}
