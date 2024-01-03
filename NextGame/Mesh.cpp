#include "stdafx.h"
#include "Mesh.h"

void Mesh::Initialize() {
	Renderable::Initialize();
}

void Mesh::Update() {
	if (this->parent != nullptr) {
		matTranslate = float4x4::CreateTranslation(parent->GetTransform().position);
		matRotate = float4x4::CreateRotation(parent->GetTransform().rotation);
	}
}

void Mesh::Destroy() {

}

void Mesh::LoadMesh() {
	tris = {
		// SOUTH
		{ {0.0f, 0.0f, 0.0f},    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },

		// EAST                                                      
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 0.0f, 1.0f} },

		// NORTH                                                     
		{ {1.0f, 0.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 0.0f, 1.0f} },

		// WEST                                                      
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 0.0f},    {0.0f, 0.0f, 0.0f} },

		// TOP                                                       
		{ {0.0f, 1.0f, 0.0f},    {0.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} },
		{ {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 0.0f} },

		// BOTTOM                                                    
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
	};

	for (auto& tri : tris) {
		tri.p0 -= float3(0.5);
		tri.p1 -= float3(0.5);
		tri.p2 -= float3(0.5);
	}
}

void Mesh::Render() {
	for (auto& tri : tris) {
		Triangle triProj = tri;
		triProj.ApplyMatrix(matRotate*matTranslate*matProj);
		triProj.Normalize();

		// Center origin and scale to screen resolution
		triProj.p0 += float3(1, 1, 0);
		triProj.p1 += float3(1, 1, 0);
		triProj.p2 += float3(1, 1, 0);
		triProj.p0.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p0.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
		triProj.p1.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p1.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
		triProj.p2.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p2.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);

		triProj.Draw();
	}
}
