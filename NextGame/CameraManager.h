#pragma once
#include "Component.h"
#include "Animator.h"
#include "ShipA.h"

class CameraManager : public Component {
	Camera* camera = nullptr;
	Animator* animator = nullptr;
	ShipA* playerA = nullptr;
	Entity* playerB = nullptr;

	float3 WideViewPosition = float3(1000, 0, 0);

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void WideView();

	void PlayerAView();
	
	void PlayerBView();
};

