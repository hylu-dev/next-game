#include "stdafx.h"
#include "CameraManager.h"

void CameraManager::Initialize() {
	animator = parentEntity->AddComponent<Animator>();
	camera = Scene::Get().GetCamera();
	playerA = Scene::Get().GetEntityByName("PlayerA")->GetComponent<ShipA>();
	camera->transform.position = WideViewPosition;
	camera->transform.rotation = float3(120, 90, 0);
}

void CameraManager::Update() {
	if (App::IsKeyPressed('1')) {
		playerA->active = false;
		WideView();
	}
	else if (App::IsKeyPressed('2')) {
		PlayerAView();
	}
	else if (App::IsKeyPressed('3')) {

	}
}

void CameraManager::Destroy() {
}

void CameraManager::WideView() {
	animator->Animate(camera->transform.position, WideViewPosition, 1.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, float3(120, 90, 0), 1.0f, new EaseInOut());
}

void CameraManager::PlayerAView() {
	animator->Animate(camera->transform.position, playerA->GetOffsetCamera(), 1.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerA->parentEntity->GetTransform().rotation, 1.0f, new EaseInOut(),
		[this]() {
			playerA->active = true;
		});
}

void CameraManager::PlayerBView() {
	animator->Animate(camera->transform.position, float3(0, 0, -100.0f), 1.0f, new EaseIn());
	animator->Animate(camera->transform.rotation, 0, 1.0f, new EaseIn());
}
