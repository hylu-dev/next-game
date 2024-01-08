#pragma once
#include "Mesh.h"
class PlaneMesh : public Mesh {
	std::vector<Triangle> GenerateMesh() override;

public:
	PlaneMesh() = default;
	PlaneMesh(unsigned int _density) : Mesh(_density) {};
};

