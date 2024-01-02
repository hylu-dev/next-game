#pragma once

#include "Triangle.h"
#include "Component.h"
#include "Renderable.h"
#include <vector>

class Mesh : public Component, public Renderable
{
private:
	std::vector<Triangle> tris;

	float4x4 matProj = float4x4::CreateProjection(90.0f, APP_VIRTUAL_WIDTH/APP_VIRTUAL_HEIGHT, 0.1f, 1000.0f);

public:
	void Initialize();

	void Update();

	void Destroy();

	void LoadMesh();

	void Render() override;
};
