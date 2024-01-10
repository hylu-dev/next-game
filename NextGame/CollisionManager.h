#pragma once

#include <list>
#include "Collider.h"

class CollisionManager {
private:
	friend Collider;
	std::list<Collider*> colliders;

public:
	static CollisionManager& Get() {
		static CollisionManager instance;
		return instance;
	}

	void Initialize();

	void Update();

	void Destroy();

private:
	CollisionManager() = default;
	CollisionManager	Renderer(const Renderer&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	void AddCollider(Collider* collider);

	void RemoveCollider(Collider* collider);
};

