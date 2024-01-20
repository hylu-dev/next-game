#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

void Entity::Initialize() {

}

void Entity::Update() {
	for (auto& component : components) {
		if (component->active) {
			component->Update();
		}
	}
}

void Entity::Destroy() {
	for (auto& component : components) {
		component->Destroy();
		delete component;
		component = nullptr;
	}
	components.clear();
}
