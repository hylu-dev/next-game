#include "stdafx.h"
#include "CameraManager.h"

void CameraManager::Initialize() {
	animator = parentEntity->AddComponent<Animator>();
	camera = Scene::Get().GetCamera();
	playerA = Scene::Get().GetEntityByName("PlayerA")->GetComponent<Ship>();
	playerB = Scene::Get().GetEntityByName("PlayerB")->GetComponent<Ship>();
	camera->transform.position = float3(1000, 0, 0);
	camera->transform.rotation = float3(0, 90, 0);
}

void CameraManager::Update() {
	if (App::IsKeyPressed('1')) {
		playerA->active = false;
		playerB->active = false;
		WideView();
	}
	else if (App::IsKeyPressed('2')) {
		playerB->active = false;
		PlayerAView();
	}
	else if (App::IsKeyPressed('3')) {
		playerA->active = false;
		PlayerBView();
	}
}

void CameraManager::Destroy() {
}

void CameraManager::WideView() {
	animator->Animate(camera->transform.position, float3(1000, 0, 0), 1.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, float3(0, 90, 0), 1.0f, new EaseInOut());
}

void CameraManager::PlayerAView() {
	animator->Animate(camera->transform.position, playerA->GetOffsetCamera(), 1.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerA->parentEntity->GetTransform().rotation, 1.0f, new EaseInOut(),
		[this]() {
			playerA->active = true;
		});
}

void CameraManager::PlayerBView() {
	animator->Animate(camera->transform.position, playerB->GetOffsetCamera(), 1.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerB->parentEntity->GetTransform().rotation, 1.0f, new EaseInOut(),
		[this]() {
			playerB->active = true;
		});
}
