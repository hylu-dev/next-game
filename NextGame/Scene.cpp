#include "stdafx.h"
#include "Scene.h"

void Scene::Initialize() {

}

void Scene::Update() {
	for (auto& entity : entities) {
		entity->Update();
	}
}

void Scene::Destroy() {
	for (auto& entity : entities) {
		delete entity;
		entity = nullptr;
	}
	entities.clear();
}
