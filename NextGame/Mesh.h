#pragma once

#include "Triangle.h"
#include "Component.h"
#include "Renderable.h"
#include <vector>

class Mesh : public Component, public Renderable
{
private:
	std::vector<Triangle> tris;

	float rotation = 0.0f;

	float4x4 matProj = float4x4::CreateProjection(90.0f, APP_VIRTUAL_WIDTH/APP_VIRTUAL_HEIGHT, 0.1f, 1000.0f);
	float4x4 matRotate = float4x4::CreateRotation(float3::Zero);
	float4x4 matTranslate = float4x4::CreateTranslation(float3::Zero);

public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void LoadMesh();

	void Render() override;
};
