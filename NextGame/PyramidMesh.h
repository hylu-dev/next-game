#pragma once
#include "Mesh.h"

class PyramidMesh : public Mesh {
	std::vector<Triangle> GenerateMesh() override;

public:
	PyramidMesh() = default;
	PyramidMesh(unsigned int _density) : Mesh(_density) {};
};

