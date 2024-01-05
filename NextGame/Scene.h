#pragma once

#include <list>

class Entity;

class Scene
{
private:
	std::list<Entity*> entities;
	float4x4 view;
	float4x4 projection;


public:
	void Initialize();

	void Update();

	void Destroy();

	void CreateCamera() {};

	Entity* CreateEntity();

	void RemoveEntity(Entity* entity);
};

