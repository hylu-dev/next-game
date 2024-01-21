#include "stdafx.h"
#include "ViewManager.h"
#include "Prefabs.h"

void ViewManager::Initialize() {
	camera = Scene::Get().GetCamera();
	menuUI = parentEntity->GetComponent<MenuUI>();
	assert(menuUI != nullptr);

	playerA = Scene::Get().GetEntityByName("PlayerA")->GetComponent<Ship>();
	assert(playerA != nullptr);
	playerA->AddObserver(this);
	playerB = Scene::Get().GetEntityByName("PlayerB")->GetComponent<Ship>();
	assert(playerB != nullptr);
	playerB->AddObserver(this);

	darkStar = Scene::Get().GetEntityByName("DarkStarSphere")->GetComponent<DarkStar>();
	assert(darkStar != nullptr);
	darkStar->AddObserver(this);

	animator = parentEntity->AddComponent<Animator>();

	camera->transform.position = float3(1000, 0, 0);
	camera->transform.rotation = float3(0, 90, 0);
}

void ViewManager::Update() {
	menuUI->pulsesLeft = darkStar->health;
	if (App::IsKeyPressed(VK_RETURN)) {
		if (!enterPressed) {
			if (menuUI->isStart) {
				menuUI->isStart = false;
				PlayerAView();
			}
			else if (menuUI->isWin) {

			}
			else {
				menuUI->ClearMenu();
				CycleTurn();
			}
			App::PlaySoundW("Assets/SoundEffects/Beep.wav");
		}
		enterPressed = true;
	}
	else {
		enterPressed = false;
	}

	// Helper Utilities
	if (App::IsKeyPressed('Z')) {
		WideView();
	}
	else if (App::IsKeyPressed('X')) {
		PlayerAView();
	}
	else if (App::IsKeyPressed('C')) {
		PlayerBView();
	}
	else if (App::IsKeyPressed('V')) {
		playerA->scrap = 1000;
		playerA->fuel = 100;
		playerA->bulletLoaded = true;
	}

	playerA->active = activePlayer == playerA;
	playerB->active = activePlayer == playerB;
}

void ViewManager::Destroy() {
}

void ViewManager::WideView() {
	activePlayer = nullptr;
	animator->Animate(camera->transform.position, float3(1000, 0, 0), 1.0f, new EaseOut());
	animator->Animate(camera->transform.rotation, float3(0, 90, 0), 1.0f, new EaseOut());
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
	playerA->Reload();
	playerB->Reload();
	turns%2 == 0 ? PlayerBView() : PlayerAView();
	turns++;
}

void ViewManager::Start() {
	darkStar = (DarkStar*)Prefabs::DarkStarSphere(Transform(0, 0, 500));
	darkStar->AddObserver(this);
	playerA = (Ship*)Prefabs::PlayerA(Transform({ 0,0,-600 }, 0, { 3, 3, 6 }));
	playerA->AddObserver(this);
	playerB = (Ship*)Prefabs::PlayerB(Transform({ 0,0,-600 }, { 0,180,0 }, { 3, 2, 6 }));
	playerB->AddObserver(this);
}

void ViewManager::Restart() {
	Scene::Get().RemoveEntity(darkStar->parentEntity);
	Scene::Get().RemoveEntity(playerA->parentEntity);
	Scene::Get().RemoveEntity(playerB->parentEntity);
}

void ViewManager::OnNotify(const Entity* entity, GameEvent event) {
	switch (event) {
	case PLAYERA_WIN:
		menuUI->WinMenu("Green");
		WideView();
		break;

	case PLAYERB_WIN:
		menuUI->WinMenu("Red");
		WideView();
		break;

	case STAR_PULSE:
		playerA->fuel = 100;
		playerB->fuel = 100;
		menuUI->TurnMenu(activePlayer);
		WideView();
		break;
	case SUPERNOVA:
		WideView();
	default:
		break;
	}
}
