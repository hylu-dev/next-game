#pragma once

#include <list>
#include "Camera.h"

class Entity;

class Scene
{
private:
	std::list<Entity*> entities;
	Camera* camera;

public:
	void Initialize(float _fov, float _near, float _far);

	void Update();

	void Destroy();

	Camera* GetCamera() { return camera; }

	Entity* CreateEntity(std::string name);

	//Entity* GetEntity();

	void RemoveEntity(Entity* entity);
};

