#pragma once

#include "Entity.h"

class Component {
public:
	Entity* parentEntity = nullptr;

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;
};

