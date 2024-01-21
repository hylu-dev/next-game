#pragma once
#include "Component.h"
#include "Animator.h"
#include "Ship.h"

class CameraManager : public Component {
	Camera* camera = nullptr;
	Animator* animator = nullptr;
	Ship* playerA = nullptr;
	Ship* playerB = nullptr;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void WideView();

	void PlayerAView();
	
	void PlayerBView();
};

