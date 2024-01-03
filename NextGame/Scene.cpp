#include "stdafx.h"
#include "Scene.h"
#include "Mesh.h"

void Scene::Initialize() {
	for (auto& entity : entities) {
		entity->Initialize();
	}
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

Entity* Scene::CreateEntity() {
	Entity* newEntity = new Entity();
	entities.push_back(newEntity);
	newEntity->Initialize();
	return newEntity;
}

void Scene::RemoveEntity(Entity* entity) {
}
