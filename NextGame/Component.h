#pragma once

class Entity;

class Component
{
public:
	Entity* entity = nullptr;

	void Initialize();

	void Update();

	void Destroy();
};

