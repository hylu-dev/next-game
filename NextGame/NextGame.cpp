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
#include "PlaneMesh.h"
#include "Prefabs.h"

Scene* mainScene = new Scene();

std::vector<Entity*> actors;

void Init()
{
	Time::Get().Initialize();
	Renderer::Get().Initialize();
	mainScene->Initialize();

	Prefabs::RippleCube(mainScene, Transform(
		float3(0, 0, 70.0f),
		float3(30.0f, 40.0f, 0.0f),
		float3(50.0f)
	));
	/*Prefabs::RipplePlane(mainScene, Transform(
		float3(0, 0, 70.0f),
		float3(30.0f, 0.0f, 0.0f),
		float3(100.0f, 1.0f, 100.0f)
	));*/
}

// Ignore deltaTime parameter as I'm using my own implementation
void Update(float deltaTime)
{
	Time::Get().Update();
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