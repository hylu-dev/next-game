#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

void Entity::SetActive(bool state) {
	active = state;
	if (!active) {
		for (auto& component : components) {
			component->active = false;
		}
	}
}

void Entity::Initialize() {

}

void Entity::Update() {
	transform.rotation.x = fmod(transform.rotation.x, 360.0);
	transform.rotation.y = fmod(transform.rotation.y, 360.0);
	transform.rotation.z = fmod(transform.rotation.z, 360.0);

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
