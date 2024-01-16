#pragma once

#include <list>
#include "Collider.h"

class CollisionManager {
private:
	friend Collider;

	std::list<Collider*> colliders;
	std::list<std::pair<Collider*, Collider*>> collisions;
	static CollisionManager* instance;

public:
	static CollisionManager& Get() {
		if (instance == nullptr) {
			instance = new CollisionManager();
			instance->Initialize();
		}
		return *instance;
	}

	void Initialize();

	void Update();

	void Destroy();

private:
	CollisionManager() = default;
	CollisionManager Renderer(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	void AddCollider(Collider* collider);

	void RemoveCollider(Collider* collider);
};

