#pragma once

#include "Entity.h"

class Component
{
public:
	Entity* parent = nullptr;

	virtual void Initialize();

	virtual void Update();

	virtual void Destroy();
};

