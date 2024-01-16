#pragma once

#include "Collider.h"

class SphereCollider : public Collider {
public:
	float radius = 1.0f;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	ColliderType GetType() override;

	void Collide(Collider* other) override;
};

