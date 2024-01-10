#pragma once

#include "Collider.h"

class BoxCollider : public Collider {
public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void Collide(Collider* other) override;
};

