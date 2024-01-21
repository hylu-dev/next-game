#include "stdafx.h"
#include "DarkStar.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "TimingFunction.h"

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
		if (c2->parentEntity->Name() == "Bullet") {
			Scene::Get().RemoveEntity(c2->parentEntity);
			animator->Animate(parentEntity->GetTransform().scale, parentEntity->GetTransform().scale * 0.9, 0.5f, new ElasticEaseOut);
			animator->Animate(parentEntity->GetTransform().rotation, parentEntity->GetTransform().rotation + float3(0,180,0), 0.8, new EaseInOut);
			SphereCollider* c = static_cast<SphereCollider*>(c1);
			c->radius = parentEntity->GetTransform().scale.x*0.9;
			pulseEmitter->Emit();
			shaderStability += 0.04f;
			shaderSpeed += 2.0f;
			meshFilter->Color().y += 0.1;

			notify(GameEvent::STAR_PULSE);
		}
		});

	pulseEmitter = parentEntity->AddComponent<ParticleEmitter>();
	pulseEmitter->burstSize = 300;
	pulseEmitter->active = false;
	pulseEmitter->lifetime = 2.0f;
	pulseEmitter->size = 30;
	pulseEmitter->color = color;
	pulseEmitter->shape = EmissionShape::RADIAL;
	pulseEmitter->speed = 200.0f;

	constantEmitter = parentEntity->AddComponent<ParticleEmitter>();
	constantEmitter->burstSize = 10;
	constantEmitter->frequency = 0.05f;
	constantEmitter->lifetime = 1.0f;
	constantEmitter->size = 20;
	constantEmitter->color = color;
	constantEmitter->shape = EmissionShape::RADIAL;
	constantEmitter->speed = 50.0f;
}

void DarkStar::Update() {
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
