#include "stdafx.h"
#include "Prefabs.h"
// Components
#include "Animator.h"
#include "Animation.h"
#include "MeshFilter.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "BoxCollider.h"
// Custom Components
#include "DarkStar.h"
#include "Ship.h"
#include "ViewManager.h"
#include "PlayerUI.h"
#include "Asteroid.h"
#include "MenuUI.h"
#include "CameraController.h"

IMPLEMENT_PREFAB(DarkStarSphere, {
	entity->AddComponent<DarkStar>();
	});

IMPLEMENT_PREFAB(PlayerA, {
	Ship* ship = entity->AddComponent<Ship>();
	ship->SetColor(float3(0, 1, 0));
	entity->AddComponent<PlayerUI>();
	});

IMPLEMENT_PREFAB(PlayerB, {
	Ship* ship = entity->AddComponent<Ship>();
	ship->SetColor(float3(1, 0, 0));
	entity->AddComponent<PlayerUI>();
	});


IMPLEMENT_PREFAB(GameManager, {
	entity->AddComponent<MenuUI>();
	entity->AddComponent<ViewManager>();
	})

IMPLEMENT_PREFAB(AsteroidObject, {
	entity->AddComponent<Asteroid>();
	});

IMPLEMENT_PREFAB(Wall, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(1));
	meshFilter->SetColor(float3(0.3f, 0.8f, 1.0f));
	BoxCollider* collider = entity->AddComponent<BoxCollider>();
	collider->dimensions = offset.scale;
	});


IMPLEMENT_PREFAB(RipplePlane, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(30));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;
		height += 5.0f * sinf(2.0f * Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
		+ sinf(Time::Get().Elapsed() + vertex.x * vertex.z)
		);
		height = std::round(height);
		vertex.y += height;
		});
	});

IMPLEMENT_PREFAB(Checker, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(20));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;

		height += 0.5f * sinf(20.0f * vertex.x + 5.0f);
		height += 0.5f * sinf(20.0f * vertex.z);
		height = 3.0f * std::floor(height);
		vertex.y += height;
		});
	});

IMPLEMENT_PREFAB(Pillar, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(5));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;
		height += std::exp(
			vertex.Distance(float3(0, 0, 0))*5
		);
		vertex.y += height;
		});
	});

IMPLEMENT_PREFAB(Ball, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(SphereMesh(3));
	});

IMPLEMENT_PREFAB(Triangle, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PyramidMesh(2));
	});

IMPLEMENT_PREFAB(RippleCube, {
	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(5));
	meshFilter->SetVertexShader([](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0, 0.5, 0));
		displace *= 0.03f * (5.0f - 5.0f * dist) * sinf(20.0f * dist - 5.0f);
		vertex += displace;
		});
	});

IMPLEMENT_PREFAB(PlayerCamera, {
	entity->AddComponent<CameraController>();
	});

IMPLEMENT_PREFAB(EasingBox, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(5));
	Animator* animator = entity->AddComponent<Animator>();

	animator->Animate(entity->GetTransform().position, float3(30, 0, 50), 0.75f, new Linear(), nullptr, 5.0f)->Then(
		entity->GetTransform().position, float3(30, 0, 50), 1.0f, new EaseInOut(), 1.0f)->Then(
		entity->GetTransform().position, float3(30, 0, 50), 1.0f, new EaseInOutBack(), 1.25f)->Then(
		entity->GetTransform().position, float3(30, 0, 50), 1.5f, new ElasticEaseOut(), 1.25f);

	animator->Animate(meshFilter->color, float3(1), 0.75f, new Linear(), nullptr, 5.0f)->Then(
		meshFilter->color, float3(1, 0, 0), 1.0f, new EaseInOut(), 1.0f)->Then(
			meshFilter->color, float3(0, 1, 0), 1.0f, new EaseInOutBack(), 1.25f)->Then(
				meshFilter->color, float3(0, 1, 1), 1.5f, new ElasticEaseOut(), 1.25f);
		});

IMPLEMENT_PREFAB(MeshDensity, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->SetVertexShader([](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0, 0.5, 0));
		displace *= 0.03f * (5.0f - 5.0f * dist) * sinf(20.0f * dist - 5.0f * Time::Get().Elapsed());
		vertex += displace;
		});

	Animator* animator = entity->AddComponent<Animator>();
	animator->Animate(meshFilter->density, 20, 5.0f, new Linear(), nullptr, 5);

	});

