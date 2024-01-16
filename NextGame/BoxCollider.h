#pragma once

#include "Collider.h"

class BoxCollider : public Collider {
public:
	float3 dimensions = float3::One;

	void Initialize() override;

	void Update() override;

	void Destroy() override;

	ColliderType GetType() override;

	void Collide(Collider* other) override;
};

