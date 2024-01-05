#include "stdafx.h"
#include "Scene.h"
#include "MeshFilter.h"

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
		entity->Destroy();
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
