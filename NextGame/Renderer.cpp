#include "stdafx.h"
#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Initialize() {
	depthBuffer = new float[APP_VIRTUAL_WIDTH * APP_VIRTUAL_HEIGHT];
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
	delete depthBuffer;
	delete instance;
}

void Renderer::AddRenderable(Renderable* renderable) {
	renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(Renderable* renderable) {
	renderables.remove(renderable);
}