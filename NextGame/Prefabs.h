#pragma once

#include "Scene.h"

#define DEFINE_PREFAB(name) \
	void name(Transform offset);

#define IMPLEMENT_PREFAB(name, implementation) \
    void Prefabs::name(Transform offset) { \
		Entity* entity = Scene::Get().CreateEntity(#name); \
		entity->GetTransform().position += offset.position; \
		entity->GetTransform().rotation += offset.rotation; \
		entity->GetTransform().scale *= offset.scale; \
        implementation \
    }

class Entity;

namespace Prefabs {
	
	DEFINE_PREFAB(DarkStarSphere);
	DEFINE_PREFAB(PlayerA);
	DEFINE_PREFAB(CameraSystem);

	/*
	DEFINE_PREFAB(Player);
	DEFINE_PREFAB(EnemyBox);
	DEFINE_PREFAB(Wall);
	DEFINE_PREFAB(RipplePlane);
	DEFINE_PREFAB(Checker);
	DEFINE_PREFAB(Pillar);
	DEFINE_PREFAB(RippleCube);
	DEFINE_PREFAB(PlayerCamera);
	DEFINE_PREFAB(RipplePlane);*/
};

