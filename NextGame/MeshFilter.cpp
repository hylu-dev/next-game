#include "stdafx.h"
#include "MeshFilter.h"

void MeshFilter::Initialize() {
	Renderable::Initialize();
}

void MeshFilter::Update() {
	if (this->parent != nullptr) {
		matScale = float4x4::CreateScale(parent->GetTransform().scale);
		matRotate = float4x4::CreateRotation(parent->GetTransform().rotation);
		matTranslate = float4x4::CreateTranslation(parent->GetTransform().position);
	}
}

void MeshFilter::Destroy() {

}

void MeshFilter::LoadMesh(Mesh& mesh) {
	tris = mesh.GenerateMesh();
}

void MeshFilter::Render() {
	for (auto& tri : tris) {
		Triangle triTransformed = tri;

		if (vertexShader != nullptr) {
			vertexShader(triTransformed.p0);
			vertexShader(triTransformed.p1);
			vertexShader(triTransformed.p2);
		}
		// Transform
		triTransformed.ApplyMatrix(matScale*matRotate*matTranslate);

		// Backface culling
		float3 normal = triTransformed.CalcNormal();
		normal.Normalize();

		// Temp
		float3 camera = float3::Zero;

		if (normal.Dot(triTransformed.p0 - camera) < 0) {
			// Project 3D -> 2D 
			triTransformed.ApplyMatrix(matProj);
			triTransformed.Normalize();
			// Center origin and scale to screen resolution
			triTransformed = triTransformed + float3(1, 1, 0);
			triTransformed.p0.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p0.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
			triTransformed.p1.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p1.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
			triTransformed.p2.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p2.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);

			triTransformed.Draw();
		}
	}
}
