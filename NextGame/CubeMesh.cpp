#include "stdafx.h"
#include "CubeMesh.h"

std::vector<Triangle> CubeMesh::GenerateMesh() {
    const float vertexLength = 1.0f / (vertexDensity);
    // Creates a square out of two tris
    auto square = [](float length, float3 position) {
        std::vector<Triangle> squareTris;
        squareTris = {
            Triangle(
                float3( 0.0f, 0.0f, 0.0f ) + position,
                float3(0.0f, length, 0.0f ) + position,
                float3(length, length, 0.0f ) + position
            ),
            Triangle(
                float3( length, length, 0.0f ) + position,
                float3( length, 0.0f, 0.0f ) + position,
                float3( 0.0f, 0.0f, 0.0f ) + position
            )
        };
        return squareTris;
    };

    for (int i = 0; i < vertexDensity; i++) {
        for (int j = 0; j < vertexDensity; j++) {
            std::vector<Triangle> squareTris = square(vertexLength, float3(vertexLength*i, vertexLength*j, 0.0f));
            tris.insert(tris.begin(), squareTris.begin(), squareTris.end());
        }
    }



    return tris;
}
