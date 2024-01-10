#pragma once

#include "Component.h"

class Collider : Component {
public:
	void Initialize() = 0;

	void Update() = 0;

	void Destroy() = 0;

	virtual void Collide(Collider* other) = 0;
};

