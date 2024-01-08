#include "stdafx.h"
#include "CubeMesh.h"

enum Face {
    SOUTH,
    WEST,
    EAST,
    NORTH,
    TOP,
    BOTTOM
};

std::vector<Triangle> CubeMesh::GenerateMesh() {
    const float vertexLength = 1.0f / (vertexDensity);
    for (int i = 0; i < vertexDensity; i++) {
        for (int j = 0; j < vertexDensity; j++) {
            // SOUTH
            tris.push_back(Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, vertexLength, 0.0f),
                float3(vertexLength, vertexLength, 0.0f)
            ) + float3(vertexLength * i, vertexLength * j, 0.0f));
            tris.push_back(Triangle(
                float3(vertexLength, vertexLength, 0.0f),
                float3(vertexLength, 0.0f, 0.0f),
                float3(0.0f, 0.0f, 0.0f)
            ) + float3(vertexLength * i, vertexLength * j, 0.0f));
            // EAST
            tris.push_back(Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, vertexLength, 0.0f),
                float3(0.0f, vertexLength, vertexLength)
            ) + float3(1.0f, vertexLength * j, vertexLength * i));
            tris.push_back(Triangle(
                float3(0.0f, vertexLength, vertexLength),
                float3(0.0f, 0.0f, vertexLength),
                float3(0.0f, 0.0f, 0.0f)
            ) + float3(1.0f, vertexLength * j, vertexLength * i));
            // NORTH
            tris.push_back(Triangle(
                float3(vertexLength, 0.0f, 0.0f),
                float3(vertexLength, vertexLength, 0.0f),
                float3(0.0f, vertexLength, 0.0f)
            ) + float3(1.0f- (vertexLength + vertexLength * i), vertexLength * j, 1.0f));
            tris.push_back(Triangle(
                float3(0.0f, vertexLength, 0.0f),
                float3(0.0f, 0.0f, 0.0f),
                float3(vertexLength, 0.0f, 0.0f)
            ) + float3(1.0f - (vertexLength + vertexLength* i), vertexLength * j, 1.0f));
            // WEST
            tris.push_back(Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, vertexLength, 0.0f),
                float3(0.0f, vertexLength, -vertexLength)
            ) + float3(0.0f, vertexLength * j, 1.0f - vertexLength * i));
            tris.push_back(Triangle(
                float3(0.0f, vertexLength, -vertexLength),
                float3(0.0f, 0.0f, -vertexLength),
                float3(0.0f, 0.0f, 0.0f)
            ) + float3(0.0f, vertexLength * j, 1.0f - vertexLength * i));
            // TOP
            tris.push_back(Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, 0.0f, vertexLength),
                float3(vertexLength, 0.0f, vertexLength)
            ) + float3(vertexLength * i, 1.0f, vertexLength * j));
            tris.push_back(Triangle(
                float3(vertexLength, 0.0f, vertexLength),
                float3(vertexLength, 0.0f, 0.0f),
                float3(0.0f, 0.0f, 0.0f)
            ) + float3(vertexLength * i, 1.0f, vertexLength * j));
            // BOTTOM
            tris.push_back(Triangle(
                float3(0.0f, 0.0f, 0.0f),
                float3(0.0f, 0.0f, -vertexLength),
                float3(vertexLength, 0.0f, -vertexLength)
            ) + float3(vertexLength * i, 0.0f, 1.0f - vertexLength * j));
            tris.push_back(Triangle(
                float3(vertexLength, 0.0f, -vertexLength),
                float3(vertexLength, 0.0f, 0.0f),
                float3(0.0f, 0.0f, 0.0f)
            ) + float3(vertexLength * i, 0.0f, 1.0f - vertexLength * j));
        }
    }

    // Center origin
    for (auto& tri : tris) {
        tri = tri - 0.5f;
    }

    return tris;
}
