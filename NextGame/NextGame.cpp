//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app\app.h"

#include "Scene.h"
#include "MeshFilter.h"
#include "CubeMesh.h"

Scene* mainScene = new Scene();

std::list<Entity*> actors;
float timeTest = 0.0f;

void Init()
{
	Renderer::Get().Initialize();
	mainScene->Initialize();

	for (int i = 0; i < 1; i++) {
		Entity* actor = mainScene->CreateEntity();
		actors.push_back(actor);

		MeshFilter* meshFilter = actor->AddComponent<MeshFilter>();
		CubeMesh cb(50);
		meshFilter->LoadMesh(cb);

		meshFilter->setVertexShader([](float3& vertex) {
			float height = vertex.z;
			height += 5.0f*sinf(timeTest + (vertex.x +vertex.y)*10.0f);
			height += 5.0f * sinf(timeTest + vertex.Distance(float3(0, 0, 0)) * 30.0f);
			vertex.z += height;
			});
		
		actor->GetTransform().scale = float3(100.0f, 100.0f, 1.0f);
		actor->GetTransform().position.z = 80.0f;
		actor->GetTransform().rotation = float3(
			-60.0f,
			15.0f,
			0.0f
		);
	}
}

void Update(float deltaTime)
{
	timeTest += 0.05f;
	for (auto& actor : actors) {
		actor->GetTransform().rotation.z += 0.2f;
	}
	mainScene->Update();
}

void Render()
{	
	Renderer::Get().Update();
}

void Shutdown()
{	
	Renderer::Get().Destroy();
}