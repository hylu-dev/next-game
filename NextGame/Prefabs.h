#pragma once

#include "Scene.h"

#define DEFINE_PREFAB(name) \
	void name(Scene* scene, Transform offset);

#define IMPLEMENT_PREFAB(name, implementation) \
    void Prefabs::name(Scene* scene, Transform offset) { \
		Entity* entity = scene->CreateEntity(#name); \
		entity->GetTransform().position += offset.position; \
		entity->GetTransform().rotation += offset.rotation; \
		entity->GetTransform().scale *= offset.scale; \
        implementation \
    }

class Entity;

namespace Prefabs {
	DEFINE_PREFAB(PlayerCube);
	DEFINE_PREFAB(Wall);

	DEFINE_PREFAB(RipplePlane);
	DEFINE_PREFAB(Checker);
	DEFINE_PREFAB(Pillar);
	DEFINE_PREFAB(RippleCube);
	DEFINE_PREFAB(PlayerCamera);
	DEFINE_PREFAB(RipplePlane);
};

