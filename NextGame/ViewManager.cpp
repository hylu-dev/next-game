#include "stdafx.h"
#include "ViewManager.h"

void ViewManager::Initialize() {
	menuUI = parentEntity->GetComponent<MenuUI>();
	assert(menuUI != nullptr);
	camera = Scene::Get().GetCamera();
	playerA = Scene::Get().GetEntityByName("PlayerA")->GetComponent<Ship>();
	assert(playerA != nullptr);
	playerA->addObserver(this);
	playerB = Scene::Get().GetEntityByName("PlayerB")->GetComponent<Ship>();
	assert(playerA != nullptr);
	playerB->addObserver(this);

	darkStar = Scene::Get().GetEntityByName("DarkStarSphere")->GetComponent<DarkStar>();
	assert(darkStar != nullptr);
	darkStar->addObserver(this);

	animator = parentEntity->AddComponent<Animator>();

	camera->transform.position = float3(1000, 0, 0);
	camera->transform.rotation = float3(0, 90, 0);
}

void ViewManager::Update() {
	if (App::IsKeyPressed(VK_RETURN)) {
		if (!enterPressed) {
			if (menuUI->isStart) {
				menuUI->isStart = false;
				PlayerAView();
			}
			else {
				CycleTurn();
			}
		}
		enterPressed = true;
	}
	else {
		enterPressed = false;
	}

	// Helper Utilities
	if (App::IsKeyPressed('1')) {
		WideView();
	}
	else if (App::IsKeyPressed('2')) {
		PlayerAView();
	}
	else if (App::IsKeyPressed('3')) {
		PlayerBView();
	}

	playerA->active = activePlayer == playerA;
	playerB->active = activePlayer == playerB;
}

void ViewManager::Destroy() {
}

void ViewManager::WideView() {
	activePlayer = nullptr;
	animator->Animate(camera->transform.position, float3(1000, 0, 0), 2.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, float3(0, 90, 0), 2.0f, new EaseInOut());
}

void ViewManager::PlayerAView() {
	activePlayer = playerA;
	animator->Animate(camera->transform.position, playerA->GetOffsetCamera(), 2.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerA->parentEntity->GetTransform().rotation, 2.0f, new EaseInOut(),
		[this]() {
			playerA->active = true;
		});
}

void ViewManager::PlayerBView() {
	activePlayer = playerB;
	animator->Animate(camera->transform.position, playerB->GetOffsetCamera(), 2.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerB->parentEntity->GetTransform().rotation, 2.0f, new EaseInOut(),
		[this]() {
			playerB->active = true;
		});
}

void ViewManager::CycleTurn() {
	turns%2 == 0 ? PlayerBView() : PlayerAView();
	turns++;
}

void ViewManager::onNotify(const Entity* entity, GameEvent event) {
	switch (event) {
	case PLAYERA_WIN:
		break;

	case PLAYERB_WIN:
		break;

	case STAR_PULSE:
		WideView();
		break;

	default:
		break;
	}
}
