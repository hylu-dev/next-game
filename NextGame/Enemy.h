#pragma once
#include "Component.h"

class Enemy : public Component {
	Entity* target = nullptr;
	float speed = 10.0f;
	float range = 40.0f;

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};

