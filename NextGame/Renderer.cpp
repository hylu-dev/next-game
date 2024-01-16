#include "stdafx.h"
#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Initialize() {
}

void Renderer::Update() {
	
}

void Renderer::Render() {
	for (auto& renderable : renderables) {
		renderable->Render();
	}
}

void Renderer::Destroy() {
	renderables.clear();
	if (instance == nullptr)
	{
		delete instance;
	}
}

void Renderer::AddRenderable(Renderable* renderable) {
	renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(Renderable* renderable) {
	renderables.remove(renderable);
}