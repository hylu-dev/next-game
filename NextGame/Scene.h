#pragma once

#include "Entity.h"
#include <list>

class Scene
{
private:
	std::list<Entity*> entities;

public:
	void Initialize();

	void Update();

	void Destroy();
};

