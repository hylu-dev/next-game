#pragma once

#include "Component.h"
#include <functional>

enum ColliderType {
	SPHERE,
	BOX
};

class Collider : public Component {

protected:
	std::function<void(Collider*)> collisionHook = nullptr;

public:
	virtual void Initialize() override;

	void Update() = 0;

	void Destroy() = 0;

	virtual ColliderType GetType() = 0;

	virtual void Collide(Collider* other) = 0;

	void SetCollisionHook(std::function<void(Collider*)> hook) { collisionHook = hook; }
};

