#include "stdafx.h"
#include "Component.h"

void Component::Initialize() {
}

void Component::Update() {
}

void Component::Destroy() {
	parentEntity = nullptr;
}
