#include "stdafx.h"
#include "PyramidMesh.h"

std::vector<Triangle> PyramidMesh::GenerateMesh() {
    // Vertices of a regular tetrahedron
    float3 v0(1.0f, 0.0f, -1.0f / std::sqrt(2.0f));
    float3 v1(-1.0f, 0.0f, -1.0f / std::sqrt(2.0f));
    float3 v2(0.0f, 1.0f, 1.0f / std::sqrt(2.0f));
    float3 v3(0.0f, -1.0f, 1.0f / std::sqrt(2.0f));

    // Base triangles
    tris.push_back(Triangle(v0, v1, v2));
    tris.push_back(Triangle(v0, v2, v3));
    tris.push_back(Triangle(v0, v3, v1));
    tris.push_back(Triangle(v1, v3, v2));

    // Need to add vertexDensity modifier...

	return tris;
}
