#include "stdafx.h"
#include "MeshFilter.h"
#include <algorithm>

void MeshFilter::Initialize() {
	Renderable::Initialize();
}

void MeshFilter::Update() {
	if (this->parentEntity != nullptr) {
		matScale = float4x4::CreateScale(parentEntity->GetTransform().scale);
		matRotate = float4x4::CreateRotation(parentEntity->GetTransform().rotation);
		matTranslate = float4x4::CreateTranslation(parentEntity->GetTransform().position);
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
		triTransformed.ApplyMatrix(matScale);
		triTransformed.ApplyMatrix(matRotate);
		triTransformed.ApplyMatrix(matTranslate);
		// Backface culling
		float3 normal = triTransformed.CalcNormal();

		if (normal.Dot(triTransformed.p0 - parentEntity->parentScene->GetCamera()->transform.position) < 0) {
			// World -> View
			triTransformed.ApplyMatrix(parentEntity->parentScene->GetCamera()->GetView());
			// Project 3D -> 2D 
			triTransformed.ApplyMatrix(parentEntity->parentScene->GetCamera()->GetProjection());

			triTransformed.p0 = triTransformed.p0 / triTransformed.p0.w;
			triTransformed.p1 = triTransformed.p1 / triTransformed.p1.w;
			triTransformed.p2 = triTransformed.p2 / triTransformed.p2.w;

			// Center origin and scale to screen resolution
			triTransformed = (triTransformed + float3(1, 1, 0))*0.5f;
			triTransformed.p0.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p0.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);
			triTransformed.p1.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p1.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);
			triTransformed.p2.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
			triTransformed.p2.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);

			triTransformed.Draw();
		}
	}
}