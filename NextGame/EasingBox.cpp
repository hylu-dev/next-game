#include "stdafx.h"
#include "EasingBox.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "Animator.h"

void EasingBox::Initialize()
{
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(4));
	meshFilter->SetColor(float3(1.0f, 0, 0));

	Animator* animator = parentEntity->AddComponent<Animator>();
	animator->Animate(parentEntity->GetTransform().position, float3(0, 10, 0), 1.0f, new EaseInOut(),
		[this, animator]() {
			animator->Animate(parentEntity->GetTransform().position, float3(10, 10, 0), 1.0f, new EaseInOutBack());

		}
	);
}

void EasingBox::Update()
{
	
}

void EasingBox::Destroy()
{
}
