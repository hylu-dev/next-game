#include "stdafx.h"
#include "Bullet.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "BoxCollider.h";

#define BULLET_RANGE_LIMIT 1000
void Bullet::Initialize() {
	parentEntity->Tag() = "Bullet";
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(1));
	meshFilter->SetColor(color);
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
}

void Bullet::Update() {
	parentEntity->GetTransform().rotation.z += 100.0f*speed*Time::Get().DeltaTime();
	parentEntity->GetTransform().position += forward * speed;
	if (parentEntity->GetTransform().position.Length() > BULLET_RANGE_LIMIT) {
		Scene::Get().RemoveEntity(parentEntity);
	}
}

void Bullet::Destroy() {

}
