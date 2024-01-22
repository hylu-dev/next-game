#include "stdafx.h"
#include "Ship.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "CubeMesh.h"
#include "TimingFunction.h"
#include "Bullet.h"
#include "Animator.h"
#include "DarkStar.h"

void Ship::Initialize() {
	parentEntity->Tag() = "Ship";
	// Ship Components
	animator = parentEntity->AddComponent<Animator>();
	meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(5));
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		float3& p1 = c1->parentEntity->GetTransform().position;
		float3& p2 = c2->parentEntity->GetTransform().position;
		if (c2->parentEntity->Name() == "DarkStarSphere") {
			float3 direction = (p1 - p2).Normalized();
			p1 += direction * 20.0f * Time::Get().DeltaTime();
			animator->Animate(
				parentEntity->GetTransform().position,
				parentEntity->GetTransform().position + direction * 100.0f,
				1.0f, new EaseOut);
			DarkStar* darkStar = c2->parentEntity->GetComponent<DarkStar>();
			darkStar->Pulse();
			Hurt(30);
		}
		if (c2->parentEntity->Name() == "Scrap") {
			if (p1.Distance(p2) < 5.0f) {
				scrap += 10.0f;
				Scene::Get().RemoveEntity(c2->parentEntity);
				App::PlaySoundW("Assets/SoundEffects/Collect.wav");
			}
		}
		if (c2->parentEntity->Tag() == "Bullet" && c2->parentEntity->Name() != parentEntity->Name() + "_Bullet") {
			Hurt(10);
			Scene::Get().RemoveEntity(c2->parentEntity);
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
	bulletEmitter->speed = 50.0f;
	bulletEmitter->coneWidth = 30.0f;
	bulletEmitter->shape = EmissionShape::CONE;
	bulletEmitter->direction = parentEntity->GetTransform().rotation;

	radialEmitter = parentEntity->AddComponent<ParticleEmitter>();
	radialEmitter->burstSize = 100;
	radialEmitter->size = 2;
	radialEmitter->lifetime = 0.5f;
	radialEmitter->active = false;
	radialEmitter->speed = 50.0f;
	// Member Variables
	camera = Scene::Get().GetCamera();
}

void Ship::Update() {
	if (!active) { return; }
	trailEmitter->direction = forward * -1;

	this->MovementHandler();

	if (App::IsKeyPressed('F') && !keyFirePressed) {
		this->FireWeapon();
		keyFirePressed = true;
	}
	else if (!App::IsKeyPressed('F')){
		keyFirePressed = false;
	}

	if (scrap >= 100) {
		this->Upgrade();
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

	float deltaAcceleration = speed * acceleration * Time::Get().DeltaTime();
	float deltaFriction = 1.0 - friction * Time::Get().DeltaTime();

	if (rotationSpeed.Length() <= maxSpeed) {
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
	
	if (movement.Length() <= maxSpeed && fuel > 0) {
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
	rotationSpeed *= Utils::Logistic(distanceFromMaxRotation, 0.3);
	rotation += rotationSpeed *= deltaFriction;
	rotation.x = Utils::Clamp(rotation.x, -86, 86);

	camera->transform.rotation = rotation;
	camera->transform.position = GetOffsetCamera();
	forward = parentEntity->GetTransform().Forward();
}

void Ship::Hurt(int damage) {
	health -= damage;
	App::PlaySoundW("Assets/SoundEffects/Swoosh.wav");
	radialEmitter->Emit();
	if (health <= 0) {
		parentEntity->Name() == "PlayerA" ? Notify(GameEvent::PLAYERB_WIN) : Notify(GameEvent::PLAYERA_WIN);
		meshFilter->active = false;
	}
}

void Ship::SetColor(float3 color) {
	meshFilter->SetColor(color);
	bulletEmitter->color = color;
	radialEmitter->color = color;
}

void Ship::Upgrade() {
	if (App::IsKeyPressed('1') && !key1Pressed) {
		App::PlaySoundW("Assets/SoundEffects/Random_7.wav");
		radialEmitter->Emit();
		scrap -= 100;
		multishot++;
		key1Pressed = true;
	}
	else if (!App::IsKeyPressed('1')) { key1Pressed = false; }

	if (App::IsKeyPressed('2') && !key2Pressed) {
		App::PlaySoundW("Assets/SoundEffects/Random_7.wav");
		radialEmitter->Emit();
		scrap -= 100;
		speed += 0.5f;
		key2Pressed = true;
	}
	else if (!App::IsKeyPressed('2')) { key2Pressed = false; }

	if (App::IsKeyPressed('3') && !key3Pressed) {
		if (health < 100) {
			App::PlaySoundW("Assets/SoundEffects/Random_7.wav");
			radialEmitter->Emit();
			scrap -= 100;
			health += 20;
		}
		else {
			App::PlaySoundW("Assets/SoundEffects/Crack_3.wav");
		}
		key3Pressed = true;
	} else if (!App::IsKeyPressed('3')) { key3Pressed = false; }

	if (App::IsKeyPressed('4') && !key4Pressed) {
		if (fuel < 100) {
			App::PlaySoundW("Assets/SoundEffects/Random_7.wav");
			radialEmitter->Emit();
			scrap -= 100;
			fuel += 20;
		}
		else {
			App::PlaySoundW("Assets/SoundEffects/Crack_3.wav");
		}
		key4Pressed = true;
	}
	else if (!App::IsKeyPressed('4')) { key4Pressed = false; }
}

void Ship::FireWeapon() {
	if (ammo <= 0) {
		App::PlaySoundW("Assets/SoundEffects/Crack_3.wav");
		return;
	}
	ammo--;
	for (int i = 0; i < multishot; i++) {
		App::PlaySoundW("Assets/SoundEffects/Fire_Laser.wav");
		Entity* entity = Scene::Get().CreateEntity(parentEntity->Name() + "_Bullet");
		entity->GetTransform().position = parentEntity->GetTransform().position;
		entity->GetTransform().rotation = parentEntity->GetTransform().rotation;
		entity->GetTransform().scale = 2.0f;
		Bullet* bullet = entity->AddComponent<Bullet>();
		bullet->forward = forward + Utils::RandomFloat3(-.002f*multishot,.002f*multishot);
	}
	bulletEmitter->direction = forward;
	bulletEmitter->Emit(); 
}

float3 Ship::GetOffsetCamera() {
	return parentEntity->GetTransform().position + forward * cameraZOffset + camera->Up() * cameraYOffset;
}
