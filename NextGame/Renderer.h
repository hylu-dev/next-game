#pragma once

#include <list>
#include "Renderable.h"

class Renderer {
private:
	friend Renderable;
	std::list<Renderable*> renderables;

public:
	static Renderer& Get() {
		static Renderer instance; // The singleton instance
		return instance;
	}

	void Initialize();

	void Update();

	void Destroy();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

private:
	Renderer() = default;

	void AddRenderable(Renderable* renderable);

	void RemoveRenderable(Renderable* renderable);
};

