#pragma once
#include "Component.h"

class Scrap : public Component {
	float spawnRadius = 10.0f;
	float pickUpOffset = 15.0f;

	void Initialize() override;

	void Update() override;

	void Destroy() override;
};

