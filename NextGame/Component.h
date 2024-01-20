#pragma once

#include "Entity.h"

class Component {
public:
	bool active = true;
	Entity* parentEntity = nullptr;

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;
};

