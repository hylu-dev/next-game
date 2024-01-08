#pragma once

#include "Triangle.h"
#include "Renderable.h"
#include "Mesh.h"
#include <functional>
#include <vector>

class MeshFilter : public Renderable
{
private:
	std::vector<Triangle> tris;

	std::function<void(float3&)> vertexShader = nullptr;

	float4x4 matProj = float4x4::CreateProjection(120.0f, APP_VIRTUAL_WIDTH/APP_VIRTUAL_HEIGHT, 0.1f, 1000.0f);
	float4x4 matScale = float4x4::CreateScale(float3::One);
	float4x4 matRotate = float4x4::CreateRotation(float3::Zero);
	float4x4 matTranslate = float4x4::CreateTranslation(float3::Zero);

public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void LoadMesh(Mesh& mesh);

	void SetVertexShader(std::function<void(float3&)> shader) { vertexShader = shader; }

	void Render() override;
};
