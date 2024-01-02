#include "stdafx.h"
#include "Entity.h"

template<typename T>
T* Entity::AddComponent()
{
	T* newComponent = new T();
	components.push_back(newComponent);
	return newComponent;
}

template<typename T>
T* Entity::GetComponent()
{
	for (Component* component : components) {
		if (typeid(*component) == typeid(T)) {
			return static_cast<T*>(component);
		}
	}
	return nullptr;
}

void Entity::Initialize() {
}

void Entity::Update() {
	for (auto& component : components) {
		component->Update();
	}
}

void Entity::Destroy() {
	for (auto& component : components) {
		delete component;
		component = nullptr;
	}
	components.clear();
}
