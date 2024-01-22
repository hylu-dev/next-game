#include "stdafx.h"
#include "DarkStar.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "TimingFunction.h"
#include "Ship.h"

void DarkStar::Initialize() {
	animator = parentEntity->AddComponent<Animator>();

	meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(SphereMesh(3));
	meshFilter->SetColor(color);
	meshFilter->SetVertexShader([this](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0.05));
		float sinOffset = sinf(50.0f * dist + F_TAU - shaderSpeed * Time::Get().Elapsed());
		displace *= shaderStability * (5.0f - 5.0f * dist) * sinf(20.0f * dist + sinOffset - shaderSpeed * Time::Get().Elapsed());
		vertex += displace;
		});

	collider = parentEntity->AddComponent<SphereCollider>();
	collider->radius = parentEntity->GetTransform().scale.x;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Tag() == "Bullet") {
			Scene::Get().RemoveEntitiesByTag("Bullet");
			Pulse();
			}
		});

	pulseEmitter = parentEntity->AddComponent<ParticleEmitter>();
	pulseEmitter->burstSize = 300;
	pulseEmitter->active = false;
	pulseEmitter->lifetime = 2.0f;
	pulseEmitter->color = color;
	pulseEmitter->shape = EmissionShape::RADIAL;
	pulseEmitter->speed = 200.0f;

	constantEmitter = parentEntity->AddComponent<ParticleEmitter>();
	constantEmitter->active = true;
	constantEmitter->burstSize = 10;
	constantEmitter->frequency = 0.05f;
	constantEmitter->lifetime = 1.0f;
	constantEmitter->size = 20;
	constantEmitter->color = color;
	constantEmitter->shape = EmissionShape::RADIAL;
	constantEmitter->speed = 50.0f;

	SpawnAsteroids();
}

void DarkStar::Update() {
	pulseEmitter->size = collider->radius*0.2f;
	pulseEmitter->radialOffset = collider->radius;
	constantEmitter->radialOffset = collider->radius;

	float3& position = parentEntity->GetTransform().position;
	float3& rotation = parentEntity->GetTransform().rotation;
	float3& scale = parentEntity->GetTransform().scale;
	float speed = 10.0f * Time::Get().DeltaTime();
	rotation.x += speed;
	rotation.y += speed;

	if (App::IsKeyPressed(VK_BACK)) {
		if (!isPressed) {
			animator->Animate(rotation, rotation + float3(0, 0, +360.0f), 2.0f, new EaseInOutBack());
			pulseEmitter->Emit();
		}
		isPressed = true;
	}
	else {
		isPressed = false;
	}
}

void DarkStar::Destroy() {
}

void DarkStar::SpawnAsteroids() {
	for (int i = 0; i < 50; i++) {
		Entity* entity = Scene::Get().CreateEntity("Asteroid");
		float randomOffset = (collider->radius + Utils::RandomFloat(50, 100));
		float3 randomLocation = parentEntity->GetTransform().position + Utils::RandomFloat3(-1, 1).Normalized() * randomOffset;
		entity->GetTransform().position = randomLocation;
		entity->GetTransform().scale = 10;
		Asteroid* ast = entity->AddComponent<Asteroid>();
	}

}

void DarkStar::Pulse() {
	health--;
	if (health == 0) {
		Supernova();
		return;
	}
	else {
		pulseEmitter->Emit();
	}
	App::PlaySoundW("Assets/SoundEffects/Explosion_2.wav");
	Notify(GameEvent::STAR_PULSE);
	animator->Animate(parentEntity->GetTransform().scale, parentEntity->GetTransform().scale * 0.7, 0.5f, new ElasticEaseOut);
	animator->Animate(parentEntity->GetTransform().rotation, parentEntity->GetTransform().rotation + Utils::RandomFloat3(-360, 360), 3.0, new ElasticEaseOut);
	collider->radius = parentEntity->GetTransform().scale.x * 0.7;
	shaderStability += 0.06f;
	shaderSpeed += 2.0f;
	meshFilter->Color().y += 0.2;
	pulseEmitter->color = meshFilter->Color();
	constantEmitter->color = meshFilter->Color();
	this->PullOrbits();
}

void DarkStar::PullOrbits() {
	for (auto& entity : Scene::Get().GetEntitiesByName("Asteroid")) {
		Transform& t1 = parentEntity->GetTransform();
		Transform& t2 = entity->GetTransform();
		Asteroid* ast = entity->GetComponent<Asteroid>();
		float3 direction = (t1.position - t2.position).Normalized();
		float dist = t1.position.Distance(t2.position) - t1.scale.x;
		// Random laterial movement
		float3 randPerpendicular = direction.Cross(Utils::RandomFloat3(-1, 1)).Normalized();
		ast->animator->Animate(
			t2.position,
			t2.position + direction * dist + randPerpendicular * dist,
			2.0f,
			new EaseInOutBack
		);
	}
	for (auto& entity : Scene::Get().GetEntitiesByTag("Ship")) {
		Transform& t1 = parentEntity->GetTransform();
		Transform& t2 = entity->GetTransform();
		Ship* ship = entity->GetComponent<Ship>();
		float3 direction = (t1.position - t2.position).Normalized();
		float dist = t1.position.Distance(t2.position) - t1.scale.x;
		// Random laterial movement
		float3 randPerpendicular = direction.Cross(Utils::RandomFloat3(-1, 1)).Normalized();
		ship->animator->Animate(
			t2.position,
			t2.position + direction * dist + randPerpendicular * dist,
			2.0f,
			new EaseInOutBack
		);
	}
}

void DarkStar::Supernova() {
	App::PlaySoundW("Assets/SoundEffects/Explode.wav");
	Notify(GameEvent::SUPERNOVA);
	Scene::Get().RemoveEntitiesByTag("Asteroid");
	meshFilter->active = false;
	constantEmitter->active = false;
	pulseEmitter = parentEntity->AddComponent<ParticleEmitter>();
	pulseEmitter->burstSize = 500;
	pulseEmitter->active = false;
	pulseEmitter->lifetime = 2.0f;
	pulseEmitter->size = 30;
	pulseEmitter->color = color;
	pulseEmitter->shape = EmissionShape::RADIAL;
	pulseEmitter->speed = 500.0f;
	pulseEmitter->Emit();
}
