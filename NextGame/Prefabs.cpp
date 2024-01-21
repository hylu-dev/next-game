#include "stdafx.h"
#include "Prefabs.h"
// Components
#include "MeshFilter.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "BoxCollider.h"
// Custom Components
#include "DarkStar.h"
#include "Ship.h"
#include "ViewManager.h"
#include "PlayerUI.h"
#include "Asteroid.h"
#include "MenuUI.h"

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

//IMPLEMENT_PREFAB(Player, {
//	entity->AddComponent<PlayerController>();
//	});
//
//IMPLEMENT_PREFAB(EnemyBox, {
//	entity->AddComponent<Enemy>();
//	});
//
//
//
//IMPLEMENT_PREFAB(RipplePlane, {
//	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
//	meshFilter->LoadMesh(PlaneMesh(30));
//	meshFilter->SetVertexShader([](float3& vertex) {
//		float height = vertex.y;
//		height += 5.0f * sinf(2.0f * Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
//		+ sinf(Time::Get().Elapsed() + vertex.x * vertex.z)
//		);
//		height = std::round(height);
//		vertex.y += height;
//		});
//	});
//
//IMPLEMENT_PREFAB(Checker, {
//	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
//	meshFilter->LoadMesh(PlaneMesh(40));
//	meshFilter->SetVertexShader([](float3& vertex) {
//		float height = vertex.y;
//
//		height += 0.5f * sinf(30.0f * vertex.x + 5.0f * Time::Get().Elapsed());
//		height += 0.5f * sinf(30.0f * vertex.z);
//		height = 3.0f * std::floor(height);
//		vertex.y += height;
//		});
//	});
//
//IMPLEMENT_PREFAB(Pillar, {
//	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
//	meshFilter->LoadMesh(PlaneMesh(20));
//	meshFilter->SetVertexShader([](float3& vertex) {
//		float height = vertex.y;
//		height += std::exp(
//			std::round(
//				5.0f * sinf(2.0f * Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
//				)
//			)
//		);
//		vertex.y += height;
//		});
//	});
//
//IMPLEMENT_PREFAB(RippleCube, {
//	MeshFilter * meshFilter = entity->AddComponent<MeshFilter>();
//	meshFilter->LoadMesh(CubeMesh(30));
//	meshFilter->SetVertexShader([](float3& vertex) {
//		float3 displace = vertex;
//		float dist = vertex.Distance(float3(0, 0.5, 0));
//		displace *= 0.03f * (5.0f - 5.0f * dist) * sinf(20.0f * dist - 5.0f * Time::Get().Elapsed());
//		vertex += displace;
//		});
//	});
//
//IMPLEMENT_PREFAB(PlayerCamera, {
//	entity->AddComponent<CameraController>();
//	});
