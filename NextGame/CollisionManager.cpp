#include "stdafx.h"
#include "CollisionManager.h"

void CollisionManager::Initialize() {
	for (auto& collider : colliders) {
		collider->Initialize();
	}
}

void CollisionManager::Update() {
	for (auto& collider : colliders) {
		collider->Update();
	}
}

void CollisionManager::Destroy() {
	for (auto& collider : colliders) {
		collider->Destroy();
		delete collider;
		collider = nullptr;
	}
	colliders.clear();
}

void CollisionManager::AddCollider(Collider* collider)
{
}

void CollisionManager::RemoveCollider(Collider* collider)
{
}
