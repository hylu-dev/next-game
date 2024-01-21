#include "stdafx.h"
#include "Particle.h"
#include "ParticleSystem.h"

void Particle::Initialize() {
	Renderable::Initialize();
	p1 = float3::Zero;
	p2 = float3(0, 1.0f, 0);
	
}

void Particle::PostInitialize() {
	Transform& transform = parentEntity->GetTransform();
	transform.scale = size;
	rotationDirection = float3(
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1)
	).Normalized();
	if (rotate) {
		transform.rotation = float3(
			Utils::RandomFloat(-180, 180),
			Utils::RandomFloat(-180, 180),
			Utils::RandomFloat(-180, 180)
		);
	}

	if (this->parentEntity != nullptr) {
		matScale = float4x4::CreateScale(transform.scale);
		matRotate = float4x4::CreateRotation(transform.rotation);
		matTranslate = float4x4::CreateTranslation(transform.position);
	}
}

void Particle::Update() {
	if (fade) {
		color -= Time::Get().DeltaTime()/lifetime;
	}

	Transform& transform = parentEntity->GetTransform();
	transform.position += direction * (speed * Time::Get().DeltaTime());
	if (rotate) {
		transform.rotation += rotationDirection*(rotationSpeed*Time::Get().DeltaTime());
	}
	// Set transformation matrices
	if (this->parentEntity != nullptr) {
		matScale = float4x4::CreateScale(transform.scale);
		matRotate = float4x4::CreateRotation(transform.rotation);
		matTranslate = float4x4::CreateTranslation(transform.position);
	}
	timer += Time::Get().DeltaTime();

	if (timer > lifetime) {
		ParticleSystem::Get().RemoveParticle(parentEntity);
	}
}

void Particle::Destroy() {
	Renderable::Destroy();
}

void Particle::Render() {
	float4x4 transformationMatrix = 
		matScale *
		matRotate *
		matTranslate *
		Scene::Get().GetCamera()->GetView();

	float3 p1Transformed = transformationMatrix*p1;
	float3 p2Transformed = transformationMatrix*p2;

	// Clipping
	float3 clipped[2] = { 0, 0 };

	float3::ClipAgainstPlane(
		{ 0.0f, 0.0f, Scene::Get().GetCamera()->nearPlane },
		{ 0.0f, 0.0f, Scene::Get().GetCamera()->farPlane },
		p1Transformed,
		p2Transformed,
		clipped[0],
		clipped[1]
	);

	if (clipped[0] == 0) { return; }

	p1Transformed = clipped[0];
	p2Transformed = clipped[1];

	p1Transformed = Scene::Get().GetCamera()->GetProjection() * p1Transformed;
	p2Transformed = Scene::Get().GetCamera()->GetProjection() * p2Transformed;

	p1Transformed /= p1Transformed.w;
	p2Transformed /= p2Transformed.w;

	p1Transformed = (p1Transformed + float3(1, 1, 0)) * 0.5f;
	p2Transformed = (p2Transformed + float3(1, 1, 0)) * 0.5f;

	p1Transformed.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
	p1Transformed.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);
	p2Transformed.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
	p2Transformed.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);

	App::DrawLine(
		p1Transformed.x, p1Transformed.y,
		p2Transformed.x, p2Transformed.y,
		color.x, color.y, color.z
	);
}
