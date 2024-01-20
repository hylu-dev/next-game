#include "stdafx.h"
#include "DarkStar.h"
#include "SphereCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "TimingFunction.h"

void DarkStar::Initialize() {
	animator = parentEntity->AddComponent<Animator>();

	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(SphereMesh(3));
	meshFilter->SetColor(float3(0, 1.0f, 1.0f));
	meshFilter->SetVertexShader([this](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0.05));
		float sinOffset = sinf(50.0f * dist + F_TAU - shaderSpeed * Time::Get().Elapsed());
		displace *= shaderStability * (5.0f - 5.0f * dist) * sinf(20.0f * dist + sinOffset - shaderSpeed * Time::Get().Elapsed());
		vertex += displace;
		});

	SphereCollider* collider = parentEntity->AddComponent<SphereCollider>();
	collider->radius = parentEntity->GetTransform().scale.x;
	collider->SetCollisionHook([this](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Name() == "Bullet") {
			c2->active = false;
			Scene::Get().RemoveEntity(c2->parentEntity);
			animator->Animate(parentEntity->GetTransform().scale, parentEntity->GetTransform().scale * 0.9, 0.5f, new ElasticEaseOut);
			animator->Animate(parentEntity->GetTransform().rotation, parentEntity->GetTransform().rotation + float3(0,180,0), 0.8, new EaseInOut);
			SphereCollider* c = static_cast<SphereCollider*>(c1);
			c->radius = parentEntity->GetTransform().scale.x*0.9;
			emitter->radialOffset = c->radius;
			emitter->Emit();
			shaderStability += 0.04f;
			shaderSpeed += 2.0f;
		}
		});

	emitter = parentEntity->AddComponent<ParticleEmitter>();
	emitter->burstSize = 300;
	emitter->radialOffset = parentEntity->GetTransform().scale.x;
	emitter->active = false;
	emitter->lifetime = 2.0f;
	emitter->size = 20;
	emitter->color = float3(0.0, 1.0f, 1.0f);
	emitter->shape = EmissionShape::RADIAL;
	emitter->speed = 200.0f;
}

void DarkStar::Update() {
	float3& position = parentEntity->GetTransform().position;
	float3& rotation = parentEntity->GetTransform().rotation;
	float3& scale = parentEntity->GetTransform().scale;
	float speed = 20.0f * Time::Get().DeltaTime();

	rotation.x += speed;
	rotation.y += speed;

	if (App::IsKeyPressed(VK_BACK)) {
		if (!isPressed) {
			animator->Animate(rotation, rotation + float3(0, 0, +360.0f), 2.0f, new EaseInOutBack());
			emitter->Emit();
		}
		isPressed = true;
	}
	else {
		isPressed = false;
	}
}

void DarkStar::Destroy() {
}
