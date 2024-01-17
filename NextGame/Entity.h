#pragma once

#include <list>
#include "Scene.h"

class Component;

class Entity {
private:
	friend Scene;

	unsigned int id = 0;
	std::list<Component*> components;
	Transform transform;
	std::string name = "";

public:
	Transform& GetTransform() { return transform; }
	std::string Name() { return name; }
	unsigned int Id() { return id; }

    template <typename T>
	T* AddComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		Component* newComponent = new T();
		newComponent->parentEntity = this;
		components.push_back(newComponent);
		newComponent->Initialize();
		return static_cast<T*>(newComponent);
	};

    template <typename T>
	T* GetComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		for (Component* component : components) {
			if (typeid(*component) == typeid(T)) {
				return static_cast<T*>(component);
			}
		}
		return nullptr;
	};

	void Initialize();

	void Update();

	void Destroy();
};

