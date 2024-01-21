#pragma once
#include "Component.h"
#include "Animator.h"
#include "Ship.h"
#include "MenuUI.h"
#include "Observer.h"
#include "DarkStar.h"

class ViewManager : public Component, public Observer {
	Camera* camera = nullptr;
	Animator* animator = nullptr;
	Ship* playerA = nullptr;
	Ship* playerB = nullptr;
	Ship* activePlayer = nullptr;
	DarkStar* darkStar = nullptr;

	MenuUI* menuUI = nullptr;

	bool enterPressed = false;

	int turns = 0;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void WideView();

	void PlayerAView();
	
	void PlayerBView();

	void CycleTurn();

	void Start();

	void Restart();

	void OnNotify(const Entity* entity, GameEvent event) override;
};

