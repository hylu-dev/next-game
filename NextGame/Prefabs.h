#pragma once

#include "Scene.h"

#define DEFINE_PREFAB(name) \
	Entity* name(Transform offset);

#define IMPLEMENT_PREFAB(name, implementation) \
    Entity* Prefabs::name(Transform offset) { \
		Entity* entity = Scene::Get().CreateEntity(#name); \
		entity->GetTransform().position += offset.position; \
		entity->GetTransform().rotation += offset.rotation; \
		entity->GetTransform().scale *= offset.scale; \
        implementation \
		return entity; \
    }

class Entity;

namespace Prefabs {
	DEFINE_PREFAB(GameManager);
	DEFINE_PREFAB(DarkStarSphere);
	DEFINE_PREFAB(PlayerA);
	DEFINE_PREFAB(PlayerB);
	DEFINE_PREFAB(AsteroidObject);

	DEFINE_PREFAB(Wall);

	/*
	DEFINE_PREFAB(Player);
	DEFINE_PREFAB(EnemyBox);
	
	DEFINE_PREFAB(RipplePlane);
	DEFINE_PREFAB(Checker);
	DEFINE_PREFAB(Pillar);
	DEFINE_PREFAB(RippleCube);
	DEFINE_PREFAB(PlayerCamera);
	DEFINE_PREFAB(RipplePlane);*/
};

