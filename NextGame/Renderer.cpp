#include "stdafx.h"
#include "Renderer.h"

void Renderer::Initialize() {
}

void Renderer::Update() {
	for (auto& renderable : renderables) {
		renderable->Render();
	}
}

void Renderer::Destroy() {
	renderables.clear();
}

void Renderer::AddRenderable(Renderable* renderable) {
	renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(Renderable* renderable) {
	renderables.remove(renderable);
}