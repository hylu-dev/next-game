#include "stdafx.h"
#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Initialize() {
}

void Renderer::Update() {

}

void Renderer::Render() {
	bool topRenderableFound = false;
	for (auto& renderable : renderables) {
		if (renderable->active) {
			if (topRenderable == renderable) {
				topRenderableFound = true;
			}
			else {
				renderable->Render();
			}
		}
	}
	if (topRenderableFound) {
		topRenderable->Render(); 
	}
	else {
		topRenderable = nullptr;
	}
}

void Renderer::Destroy() {
	topRenderable = nullptr;
	renderables.clear();
	delete instance;
}

void Renderer::AddRenderable(Renderable* renderable) {
	renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(Renderable* renderable) {
	renderables.remove(renderable);
}