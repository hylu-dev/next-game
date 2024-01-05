#include "stdafx.h"
#include "Renderable.h"

void Renderable::Initialize() {
	Renderer::Get().AddRenderable(this);
}

void Renderable::Update() {
}

void Renderable::Destroy() {
	
}
