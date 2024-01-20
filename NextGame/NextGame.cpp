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
#include "ParticleSystem.h"

#include <string>

std::vector<Entity*> actors;

void LoadGameObjects() {
	//App::PlaySound("Assets/Music/bg-music.wav", true);

	Prefabs::DarkStarSphere(Transform(0, 0, 500));
	Prefabs::PlayerA(Transform({0,0,-600}, 0, {4, 2, 5}));
	Prefabs::CameraSystem(Transform());
}

void Init() {
	Time::Get().Initialize();
	CollisionManager::Get().Initialize();
	ParticleSystem::Get().Initialize();
	Scene::Get().Initialize(90.0f, 0.1f, 1000.0f);
	Scene::Get().GetCamera()->transform.position.z -= 100.0f;
	Renderer::Get().Initialize();

	LoadGameObjects();
}

void Update(float deltaTime) {
	float frameTime = deltaTime * 0.001;
	// Enforce realistic frametimes during debugging
	#ifdef _DEBUG
	frameTime = Utils::Clamp(frameTime, 0.01, 0.05);
	#endif

	Time::Get().Update(frameTime);
	CollisionManager::Get().Update();
	ParticleSystem::Get().Update();
	Scene::Get().Update();
	Renderer::Get().Update();
}

void Render() {

	Renderer::Get().Render();
}

void Shutdown() {
	Time::Get().Destroy();
	Scene::Get().Destroy();
	CollisionManager::Get().Destroy();
	ParticleSystem::Get().Destroy();
	Renderer::Get().Destroy();
}