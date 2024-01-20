#include "stdafx.h"
#include "Scene.h"
#include "MeshFilter.h"

Scene* Scene::instance = nullptr;

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
		if (entity->active) {
			entity->Update();
		}
	}

	for (auto& entity : entitiesToDestroy) {
		entities.remove(entity);
		entity->Destroy();
		delete entity;
		entity = nullptr;
	}
	entitiesToDestroy.clear();
}

void Scene::Destroy() {
	camera->Destroy();
	for (auto& entity : entities) {
		entity->Destroy();
		delete entity;
		entity = nullptr;
	}
	entities.clear();
	entitiesToDestroy.clear();
	delete instance;
}

Entity* Scene::CreateEntity(std::string name) {
	Entity* newEntity = new Entity();
	newEntity->id = id_counter++;
	newEntity->name = name;
	entities.push_back(newEntity);
	newEntity->Initialize();
	return newEntity;
}

Entity* Scene::GetEntityByName(std::string name) {
	for (auto& entity : entities) {
		if (entity->Name() == name) {
			return entity;
		}
	}
	return nullptr;
}

Entity* Scene::GetEntityById(unsigned int _id)
{
	for (auto& entity : entities) {
		if (entity->Id() == _id) {
			return entity;
		}
	}
	return nullptr;
}

void Scene::RemoveEntity(Entity* entity) {
	entitiesToDestroy.push_back(entity);
}

void Scene::RemoveEntityById(unsigned int _id) {
	for (auto& entity : entities) {
		if (entity->Id() == _id) {
			entitiesToDestroy.push_back(entity);
			break;
		}
	}
}
