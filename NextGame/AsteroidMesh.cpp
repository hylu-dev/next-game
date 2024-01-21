#include "stdafx.h"
#include "AsteroidMesh.h"

std::vector<Triangle> AsteroidMesh::GenerateMesh() {
    float phi = (1.0f + sqrt(5.0f)) * 0.5f; // golden ratio
    float a = 1.0f;
    float b = 1.0f / phi;

    std::vector<float3> verts = {
        {0, b, -a}, {b, a, 0}, {-b, a, 0}, {0, b, a},
        {0, -b, a}, {-a, 0, b}, {0, -b, -a}, {a, 0, -b},
        {a, 0, b}, {-a, 0, -b}, {b, -a, 0}, {-b, -a, 0}
    };

    tris.push_back({ verts[2], verts[1], verts[0] });
    tris.push_back({ verts[1], verts[2], verts[3] });
    tris.push_back({ verts[5], verts[4], verts[3] });
    tris.push_back({ verts[4], verts[8], verts[3] });
    tris.push_back({ verts[7], verts[6], verts[0] });
    tris.push_back({ verts[6], verts[9], verts[0] });
    tris.push_back({ verts[11], verts[10], verts[4] });
    tris.push_back({ verts[10], verts[11], verts[6] });
    tris.push_back({ verts[9], verts[5], verts[2] });
    tris.push_back({ verts[5], verts[9], verts[11] });
    tris.push_back({ verts[8], verts[7], verts[1] });
    tris.push_back({ verts[7], verts[8], verts[10] });
    tris.push_back({ verts[2], verts[5], verts[3] });
    tris.push_back({ verts[8], verts[1], verts[3] });
    tris.push_back({ verts[9], verts[2], verts[0] });
    tris.push_back({ verts[1], verts[7], verts[0] });
    tris.push_back({ verts[11], verts[9], verts[6] });
    tris.push_back({ verts[7], verts[10], verts[6] });
    tris.push_back({ verts[5], verts[11], verts[4] });
    tris.push_back({ verts[10], verts[8], verts[4] });

    auto midpoint = [](const float3& v1, const float3& v2) { return (v1 + v2) * 0.5f; };

    for (int i = 0; i < vertexDensity; ++i) {
        std::vector<Triangle> newTris;
        for (const auto& tri : tris) {
            float3 m0 = midpoint(tri.p0, tri.p1);
            float3 m1 = midpoint(tri.p1, tri.p2);
            float3 m2 = midpoint(tri.p2, tri.p0);

            newTris.push_back({ tri.p0, m0, m2 });
            newTris.push_back({ tri.p1, m1, m0 });
            newTris.push_back({ tri.p2, m2, m1 });
            newTris.push_back({ m0, m1, m2 });
        }
        tris = newTris;
    }

    float rand = Utils::RandomFloatUniform()*0.5f + 0.5f;
    float rand1 = Utils::RandomFloat(-0.5, 0.5);
    float rand2 = Utils::RandomFloat(-0.5, 0.5);
    float rand3 = Utils::RandomFloat(-0.5, 0.5);

    for (auto& tri : tris) {
        for (auto& vert : tri.p) {
            float3 displace = vert;
            float dist = vert.Distance({rand1, rand2, rand3});
            displace *= rand*0.1*std::round(sinf(20.0f*rand1 + 20.0f * dist));
            vert += displace;
        }
    }

    return tris;
}
