#pragma once

#include <list>
#include "Renderable.h"

class Renderer {
private:
	friend Renderable;
	std::list<Renderable*> renderables;
	static Renderer* instance;

public:
	static Renderer& Get() {
		if (instance == nullptr) {
			instance = new Renderer();
			instance->Initialize();
		}
		return *instance;
	}

	void Initialize();

	void Update();

	void Render();

	void Destroy();

private:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void AddRenderable(Renderable* renderable);

	void RemoveRenderable(Renderable* renderable);
};

