#pragma once

#include "Mesh.h"

class SphereMesh : public Mesh {
	std::vector<Triangle> GenerateMesh() override;

public:
	SphereMesh() = default;
	SphereMesh(unsigned int _density) : Mesh(_density) {};
};

