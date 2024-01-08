#pragma once

#include "Triangle.h"

class Mesh {
protected:
	std::vector<Triangle> tris;
	int vertexDensity = 1;

public:
	Mesh() = default;
	Mesh(unsigned int _density) : vertexDensity(_density) {};

	virtual std::vector<Triangle> GenerateMesh() = 0;
};

