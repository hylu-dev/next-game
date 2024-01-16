#include "stdafx.h"
#include "Renderable.h"
#include "Renderer.h"

void Renderable::Initialize() {
	Renderer::Get().AddRenderable(this);
}

void Renderable::Destroy() {
	Renderer::Get().RemoveRenderable(this);
}
