#pragma once

#include <list>

class Entity;

struct Camera {
	float3 position;
	float3 rotation;
};

class Scene
{
private:
	std::list<Entity*> entities;
	float4x4 view;
	float4x4 projection;
	Camera camera;


public:
	void Initialize();

	void Update();

	void Destroy();

	Camera GetCamera() { return camera; }

	Entity* CreateEntity();

	void RemoveEntity(Entity* entity);
};

