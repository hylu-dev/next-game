#pragma once

#include <list>
#include "Renderable.h"

class Renderer {
private:
	friend Renderable;
	std::list<Renderable*> renderables;

public:
	static Renderer& Get() {
		static Renderer instance;
		return instance;
	}

	void Initialize();

	void Update();

	void Destroy();

private:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void AddRenderable(Renderable* renderable);

	void RemoveRenderable(Renderable* renderable);
};

