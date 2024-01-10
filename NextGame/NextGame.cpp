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

#include <string>

Scene* mainScene = new Scene();

std::vector<Entity*> actors;

float dtime = 0;

void Init() {
	Time::Get().Initialize();
	Renderer::Get().Initialize();
	mainScene->Initialize(90.0f, 0.1f, 1000.0f);

	Prefabs::PlayerCamera(mainScene);

	Prefabs::RippleCube(mainScene, Transform(
		float3(0.0f, 30.0f, 70.0f),
		float3(70.0f, 40.0f, 0.0f),
		float3(30.0f)
	));
	Prefabs::RipplePlane(mainScene, Transform(
		float3(0, -20.0f, 70.0f),
		float3(30.0f, 0.0f, 0.0f),
		float3(50.0f, 1.0f, 50.0f)
	));
}

// Ignoring deltaTime parameter as I'm using my own implementation
void Update(float deltaTime) {
	dtime = deltaTime/1000;
	Time::Get().Update();
	mainScene->Update();
}

void Render() {
	App::Print(0.0f, 500.0f, std::to_string(mainScene->GetCamera()->transform.position.x).c_str());
	App::Print(0.0f, 480.0f, std::to_string(mainScene->GetCamera()->transform.position.y).c_str());
	App::Print(0.0f, 460.0f, std::to_string(mainScene->GetCamera()->transform.position.z).c_str());
	
	App::Print(0.0f, 600.0f, std::to_string(dtime).c_str());
	Renderer::Get().Update();
}

void Shutdown() {
	Renderer::Get().Destroy();
}