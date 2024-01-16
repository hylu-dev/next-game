#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

void CollisionManager::Initialize() {
	for (auto& collider : colliders) {
		collider->Initialize();
	}
}

void CollisionManager::Update() {
	for (auto& collider : colliders) {
		collider->Update();
	}

	for (auto& source : colliders) {
		for (auto& target : colliders) {
			if (source != target) {
				source->Collide(target);
			}
		}
	}
}

void CollisionManager::Destroy() {
	colliders.clear();
	if (instance == nullptr)
	{
		delete instance;
	}
}

void CollisionManager::AddCollider(Collider* collider) {
	colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider) {
	colliders.remove(collider);
}
