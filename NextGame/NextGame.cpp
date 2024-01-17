//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app\app.h"

#include "Scene.h"
#include "Prefabs.h"
#include "Renderer.h"
#include "CollisionManager.h"

#include <string>

std::vector<Entity*> actors;

void Init() {
	Time::Get().Initialize();
	Renderer::Get().Initialize();
	CollisionManager::Get().Initialize();
	Scene::Get().Initialize(90.0f, 0.1f, 1000.0f);

	Prefabs::PlayerCamera(Transform());
	Prefabs::Player(Transform(
		float3(0, 0, 80.0f),
		0,
		float3(10.0f)
	));

	for (int i = 0; i < 10; i++) {
		Prefabs::EnemyBox(Transform(
			float3(
				Utils::RandomFloat(-100.0f, 100.0f),
				Utils::RandomFloat(-100.0f, 100.0f),
				80.0f
			),
			0,
			float3(10.0f)
		));
		Prefabs::Wall(Transform(
			float3(
				Utils::RandomFloat(-100.0f, 100.0f),
				Utils::RandomFloat(-100.0f, 100.0f),
				80.0f
			),
			0,
			float3(10.0f)
		));
	}

	/*Prefabs::Pillar(mainScene, Transform(
	float3(100, -20.0f, 100.0f),
	float3(),
	float3(50.0f, 0.2f, 50.0f)
	));*/

	/*Prefabs::RippleCube(mainScene, Transform(
		float3(0.0f, 30.0f, 70.0f),
		float3(70.0f, 40.0f, 0.0f),
		float3(30.0f)
	));*/

	//Prefabs::Checker(mainScene, Transform(
	//	float3(0, -20.0f, 100.0f),
	//	float3(30.0f, 0.0f, 0.0f),
	//	float3(80.0f, 1.0f, 80.0f)
	//));
}

void Update(float deltaTime) {
	float frameTime = deltaTime * 0.001;
	// Enforce realistic frametimes during debugging
	#ifdef _DEBUG
	frameTime = Utils::Clamp(frameTime, 0.01, 0.05);
	#endif

	Time::Get().Update(frameTime);
	Renderer::Get().Update();
	CollisionManager::Get().Update();
	Scene::Get().Update();
}

void Render() {
	App::Print(0.0f, 500.0f, std::to_string(Scene::Get().GetCamera()->transform.position.x).c_str());
	App::Print(0.0f, 480.0f, std::to_string(Scene::Get().GetCamera()->transform.position.y).c_str());
	App::Print(0.0f, 460.0f, std::to_string(Scene::Get().GetCamera()->transform.position.z).c_str());
	
	App::Print(0.0f, 600.0f, std::to_string(Time::Get().DeltaTime()).c_str());
	App::Print(0.0f, 700.0f, std::to_string(Time::Get().Elapsed()).c_str());
	Renderer::Get().Render();
}

void Shutdown() {
	Time::Get().Destroy();
	Scene::Get().Destroy();
	CollisionManager::Get().Destroy();
	Renderer::Get().Destroy();
}