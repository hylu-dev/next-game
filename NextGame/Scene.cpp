#include "stdafx.h"
#include "Scene.h"
#include "MeshFilter.h"

void Scene::Initialize(float _fov, float _near, float _far) {
	camera = new Camera(_fov, _near, _far);
	camera->Initialize();
	for (auto& entity : entities) {
		entity->Initialize();
	}
}

void Scene::Update() {
	camera->Update();
	for (auto& entity : entities) {
		entity->Update();
	}
}

void Scene::Destroy() {
	camera->Destroy();
	for (auto& entity : entities) {
		entity->Destroy();
		delete entity;
		entity = nullptr;
	}
	entities.clear();
}

Entity* Scene::CreateEntity() {
	Entity* newEntity = new Entity();
	newEntity->parentScene = this;
	entities.push_back(newEntity);
	newEntity->Initialize();
	return newEntity;
}

void Scene::RemoveEntity(Entity* entity) {
	entities.remove(entity);
}
