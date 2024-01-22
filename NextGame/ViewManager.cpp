#include "stdafx.h"
#include "ViewManager.h"
#include "Prefabs.h"
#include "Renderer.h"

void ViewManager::Initialize() {
	camera = Scene::Get().GetCamera();
	menuUI = parentEntity->GetComponent<MenuUI>();
	playerA = Scene::Get().GetEntityByName("PlayerA")->GetComponent<Ship>();
	playerA->AddObserver(this);
	playerB = Scene::Get().GetEntityByName("PlayerB")->GetComponent<Ship>();
	playerB->AddObserver(this);
	darkStar = Scene::Get().GetEntityByName("DarkStarSphere")->GetComponent<DarkStar>();
	darkStar->AddObserver(this);

	animator = parentEntity->AddComponent<Animator>();

	camera->transform.position = float3(1000, 0, 0);
	camera->transform.rotation = float3(0, 90, 0);
}

void ViewManager::Update() {
	// Enter inputs
	if (App::IsKeyPressed(VK_RETURN)) {
		if (inAnimation || menuUI->isWin || menuUI->isDraw) {
			return;
		}

		if (!enterPressed) {
			if (menuUI->isStart) {
				menuUI->TurnMenu();
				activePlayer = playerA;
			}
			CycleTurn();
			App::PlaySoundW("Assets/SoundEffects/Select_3.wav");
		}
		enterPressed = true;
	}
	else {
		enterPressed = false;
	}

	if (App::IsKeyPressed('L')) {
		playerA->health -= 1;
		playerB->health -= 1;
	}

	// Update ui values and active player
	menuUI->pulsesLeft = darkStar->health;
	menuUI->turnsUntilPulse = turnsUntilPulse;
	
	playerA->active = activePlayer == playerA;
	playerB->active = activePlayer == playerB;
}

void ViewManager::Destroy() {
	camera = nullptr;
	animator = nullptr;
	playerA = nullptr;
	playerB = nullptr;
	activePlayer = nullptr;
	darkStar = nullptr;
}

void ViewManager::WideView() {
	activePlayer = nullptr;
	inAnimation = true;
	animator->ClearAnimations();
	animator->Animate(camera->transform.position, float3(1000, 0, 0), 1.0f, new EaseOut());
	animator->Animate(camera->transform.rotation, float3(0, 90, 0), 1.0f, new EaseOut(),
		[this]() {
			inAnimation = false;
		});
}

void ViewManager::PlayerAView() {
	activePlayer = playerA;
	inAnimation = true;
	animator->ClearAnimations();
	Renderer::Get().SetTopRenderable(activePlayer->parentEntity->GetComponent<MeshFilter>());
	animator->Animate(camera->transform.position, playerA->GetOffsetCamera(), 2.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerA->parentEntity->GetTransform().rotation, 2.0f, new EaseInOut(),
		[this]() {
			playerA->active = true;
			inAnimation = false;
		});
}

void ViewManager::PlayerBView() {
	activePlayer = playerB;
	inAnimation = true;
	animator->ClearAnimations();
	Renderer::Get().SetTopRenderable(activePlayer->parentEntity->GetComponent<MeshFilter>());
	animator->Animate(camera->transform.position, playerB->GetOffsetCamera(), 2.0f, new EaseInOut());
	animator->Animate(camera->transform.rotation, playerB->parentEntity->GetTransform().rotation, 2.0f, new EaseInOut(),
		[this]() {
			playerB->active = true;
			inAnimation = false;
		});
}

void ViewManager::CycleTurn() {
	if (turnsUntilPulse == 0) { 
		darkStar->Pulse();
		return;
	}
	turns++;
	turnsUntilPulse--;
	playerA->Reload();
	playerB->Reload();
	turns%2 == 0 ? PlayerBView() : PlayerAView();
}

void ViewManager::OnNotify(const Entity* entity, GameEvent event) {
	switch (event) {
	case PLAYERA_WIN:
		playerA->health > 0 ? menuUI->WinMenu("Player 1") : menuUI->WinMenu("No one");
		WideView();
		break;

	case PLAYERB_WIN:
		playerB->health > 0 ? menuUI->WinMenu("Player 2") : menuUI->WinMenu("No one");
		WideView();
		break;
	case STAR_PULSE:
		if (menuUI->isWin) { return; }
		playerA->fuel = 100;
		playerB->fuel = 100;
		playerA->Hurt(pulseDamage);
		playerB->Hurt(pulseDamage);
		turnsUntilPulse = pulseFrequency;
		if (!menuUI->isWin) {
			menuUI->TurnMenu();
		};
		WideView();
		break;
	case SUPERNOVA:
		App::PlaySoundW("Assets/SoundEffects/Carrot.wav");
		menuUI->DrawMenu();
		WideView();
		break;
	default:
		break;
	}
}
