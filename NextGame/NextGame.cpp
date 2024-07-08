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
#include <iostream>

std::vector<Entity*> actors;
bool isRestart = false;
bool isMute = false;
const char* musicPath = "Assets/Music/bg-music.wav";


void LoadGameObjects() {
	/*Prefabs::DarkStarSphere(Transform(0, 0, 500));
	Prefabs::PlayerA(Transform({ 0,0,-600 }, 0, { 3, 3, 6 }));
	Prefabs::PlayerB(Transform({ 0,0,600 }, { 0,180,0 }, { 4, 3, 6 }));
	Prefabs::GameManager(Transform());*/

	// Primitives
	/*Prefabs::RippleCube(Transform({0, 0, 0}, 0, 10));
	Prefabs::Pillar(Transform({ 15, 0, 0}, 0, {10, 0.1, 10}));
	Prefabs::Ball(Transform({ 0, 0, 15 }, 0, { 5, 5, 5 }));
	Prefabs::Triangle(Transform({ 0, 0, -15 }, 0, { 5, 5, 5 }));
	Prefabs::Checker(Transform({-15, 0, 0}, 0, { 10, 0.5, 10 }));
	*/

	//Prefabs::EasingBox(Transform({ -30, 0, 50 }, 0, 20));

	Prefabs::MeshDensity(Transform({ 0, 0, 0 }, 0, 60));
	Prefabs::PlayerCamera(Transform());
}

void Init() {
	App::PlaySoundW(musicPath, true);

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

	if (App::IsKeyPressed('M') && !isMute) {
		App::IsSoundPlaying(musicPath) ? App::StopSound(musicPath) : App::PlaySoundW(musicPath, true);
		isMute = true;
	}
	else if (!App::IsKeyPressed('M')) { isMute = false; }

	if (App::IsKeyPressed(VK_BACK) && !isRestart) {
		Scene::Get().RemoveEntitiesByTag("Ship");
		Scene::Get().RemoveEntitiesByTag("GameManager");
		Scene::Get().RemoveEntitiesByTag("DarkStarSphere");
		Scene::Get().RemoveEntitiesByTag("Asteroid");
		Scene::Get().RemoveEntitiesByTag("Scrap");
		Time::Get().Update(frameTime);
		CollisionManager::Get().Update();
		ParticleSystem::Get().Update();
		Scene::Get().Update();
		Renderer::Get().Update();
		Prefabs::DarkStarSphere(Transform(0, 0, 500));
		Prefabs::PlayerA(Transform({ 0,0,-600 }, 0, { 4, 3, 6 }));
		Prefabs::PlayerB(Transform({ 0,0,600 }, { 0,180,0 }, { 4, 3, 6 }));
		Prefabs::GameManager(Transform());
		isRestart = true;
	}
	else if (!App::IsKeyPressed(VK_BACK)) { isRestart = false; }
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