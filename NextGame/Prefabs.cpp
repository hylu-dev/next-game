#include "stdafx.h"
#include "Prefabs.h"
#include "MeshFilter.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "CameraController.h"

void Prefabs::RipplePlane(Scene* scene, Transform offset) {
	Entity* actor = scene->CreateEntity();
	actor->GetTransform().position += offset.position;
	actor->GetTransform().rotation += offset.rotation;
	actor->GetTransform().scale *= offset.scale;

	MeshFilter* meshFilter = actor->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(PlaneMesh(30));
	meshFilter->SetVertexShader([](float3& vertex) {
		float height = vertex.y;
		height += 10.0f * sinf(
			2.0f*Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 10.0f
			+ 1.0f * sinf(Time::Get().Elapsed() + vertex.Distance(float3(0, 0, 0)) * 5.0f)
		);
		vertex.y += height;
		});

}

void Prefabs::RippleCube(Scene* scene, Transform offset) {
	Entity* actor = scene->CreateEntity();
	actor->GetTransform().position += offset.position;
	actor->GetTransform().rotation += offset.rotation;
	actor->GetTransform().scale *= offset.scale;

	MeshFilter* meshFilter = actor->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(15));
	meshFilter->SetVertexShader([](float3& vertex) {
		float3 displace = vertex;
		float dist = vertex.Distance(float3(0, 0.5, 0));
		displace *= 0.03f*(5.0f-5.0f*dist) * sinf(20.0f*dist - 5.0f * Time::Get().Elapsed());
		vertex += displace;
		});
}

void Prefabs::PlayerCamera(Scene* scene, Transform offset) {
	Entity* actor = scene->CreateEntity();
	actor->GetTransform().position += offset.position;
	actor->GetTransform().rotation += offset.rotation;
	actor->GetTransform().scale *= offset.scale;
	actor->AddComponent<CameraController>();
}
