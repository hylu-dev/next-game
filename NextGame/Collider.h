#pragma once

#include "Component.h"
#include <functional>

enum ColliderType {
	SPHERE,
	BOX
};

class Collider : public Component {

protected:
	friend class CollisionManager;

	std::function<void(Collider*, Collider*)> collisionHook = nullptr;

public:
	void Initialize() override;

	void Update() = 0;

	void Destroy() override;

	virtual ColliderType GetType() = 0;

	virtual void Collide(Collider* other) = 0;

	void SetCollisionHook(std::function<void(Collider* source, Collider* target)> hook) { collisionHook = hook; }
};

