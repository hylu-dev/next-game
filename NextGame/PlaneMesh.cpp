#include "stdafx.h"
#include "PlaneMesh.h"

std::vector<Triangle> PlaneMesh::GenerateMesh() {
    const float vertexLength = 1.0f / (vertexDensity);
    // Creates a square out of two tris
    auto square = [](float length, float3 position) {
        std::vector<Triangle> squareTris;
        squareTris = {
            Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, 0.0f, length),
                float3(length, 0.0f, length)
            ) + position,
            Triangle(
                float3(length, 0.0f, length),
                float3(length, 0.0f, 0.0f),
                float3(0.0f, 0.0f, 0.0f)
            ) + position
        };
        return squareTris;
        };

    for (int i = 0; i < vertexDensity; i++) {
        for (int j = 0; j < vertexDensity; j++) {
            std::vector<Triangle> squareTris = square(vertexLength, float3(vertexLength * i, 0.0f, vertexLength * j));
            tris.insert(tris.begin(), squareTris.begin(), squareTris.end());
        }
    }

    // Center origin
	for (auto& tri : tris) {
		tri = tri - float3(0.5, 0, 0.5);
	}

    return tris;
}
