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
	// Center origin
	for (auto& tri : tris) {
		tri.p0 -= float3(0.5);
		tri.p1 -= float3(0.5);
		tri.p2 -= float3(0.5);
	}
}

void MeshFilter::Render() {
	for (auto& tri : tris) {
		Triangle triProj = tri;
		vertexShader(triProj.p0);
		vertexShader(triProj.p1);
		vertexShader(triProj.p2);
		triProj.ApplyMatrix(matScale*matRotate*matTranslate*matProj);
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
