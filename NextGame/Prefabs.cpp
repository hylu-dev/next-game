#include "stdafx.h"
#include "Prefabs.h"
#include "MeshFilter.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "CameraController.h"

IMPLEMENT_PREFAB(RipplePlane, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(30));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;
		height += 5.0f * sinf(2.0f * Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
		+ sinf(Time::Get().Elapsed() + vertex.x * vertex.z)
		);
		height = std::round(height);
		vertex.y += height;
		});
	})

IMPLEMENT_PREFAB(Checker, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(40));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;

		height += 0.5 * sinf(30.0f * vertex.x + 5.0f * Time::Get().Elapsed());
		height += 0.5 * sinf(30.0f * vertex.z);
		height = 3.0f * std::floor(height);
		vertex.y += height;
		});
	})

IMPLEMENT_PREFAB(Pillar, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(30));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;
		height += std::exp(
			std::round(
				5.0f * sinf(2.0f * Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
				)
			)
		);
		vertex.y += height;
		});
	})

IMPLEMENT_PREFAB(RippleCube, {
	MeshFilter* meshFilter = entity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(15));
	meshFilter->SetVertexShader([](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0, 0.5, 0));
		displace *= 0.03f * (5.0f - 5.0f * dist) * sinf(20.0f * dist - 5.0f * Time::Get().Elapsed());
		vertex += displace;
		});
	})

IMPLEMENT_PREFAB(PlayerCamera, {
	entity->AddComponent<CameraController>();
	})
