#pragma once

#include "Triangle.h"
#include "Renderable.h"
#include "Mesh.h"
#include <functional>
#include <vector>

class MeshFilter : public Renderable {
private:
	std::vector<Triangle> tris;
	std::function<void(float3&)> vertexShader = nullptr;
	float3 color = float3::One;

	float4x4 matScale = float4x4::CreateScale(float3::One);
	float4x4 matRotate = float4x4::CreateRotation(float3::Zero);
	float4x4 matTranslate = float4x4::CreateTranslation(float3::Zero);

public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void LoadMesh(Mesh& mesh);

	void SetColor(float3 _color) { color = _color; }

	void SetVertexShader(std::function<void(float3&)> shader) { vertexShader = shader; }

	void Render() override;
};
