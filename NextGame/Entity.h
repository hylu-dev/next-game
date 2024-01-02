#pragma once

#include "Component.h"
#include <list>

struct Transform {
	float3 position;
	float3 rotation;
	float scale = 1.0f;
};

class Entity
{
private:
	std::list<Component*> components;
	Transform transform;

public:
	Transform& GetTransform() { return transform; }

    template <typename T>
    T* AddComponent();

    template <typename T>
	T* GetComponent();

	void Initialize();

	void Update();

	void Destroy();
};

