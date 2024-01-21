#pragma once
#include "Mesh.h"

class AsteroidMesh : public Mesh {
	std::vector<Triangle> GenerateMesh() override;

public:
	AsteroidMesh() = default;
	AsteroidMesh(unsigned int _density) : Mesh(_density) {};
};