#pragma once

#include "Mesh.h"

class CubeMesh : public Mesh {
	std::vector<Triangle> GenerateMesh() override;

public:
	CubeMesh() = default;
	CubeMesh(unsigned int _density) : Mesh(_density) {};
};

