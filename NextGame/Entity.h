#pragma once

#include <list>

class Component;

struct Transform {
	float3 position;
	float3 rotation;
	float3 scale = float3::One;
};

class Entity {
private:
	std::list<Component*> components;
	Transform transform;

public:
	Transform& GetTransform() { return transform; }

    template <typename T>
	T* AddComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		Component* newComponent = new T();
		newComponent->parent = this;
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

