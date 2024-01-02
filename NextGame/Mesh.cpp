#include "stdafx.h"
#include "Mesh.h"

void Mesh::Initialize() {
	Renderable::Initialize();
}

void Mesh::Update()
{
}

void Mesh::Destroy()
{
}

void Mesh::LoadMesh() {
	tris = {
		// SOUTH
		{ {0.0f, 0.0f, 0.0f},    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },

		// EAST                                                      
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 0.0f, 1.0f} },

		// NORTH                                                     
		{ {1.0f, 0.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 0.0f, 1.0f} },

		// WEST                                                      
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 0.0f},    {0.0f, 0.0f, 0.0f} },

		// TOP                                                       
		{ {0.0f, 1.0f, 0.0f},    {0.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} },
		{ {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 0.0f} },

		// BOTTOM                                                    
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
	};
}

void Mesh::Render()
{
	for (auto& tri : tris) {
		Triangle triProj, triTrans;

		triTrans = tri;

		triTrans.p0 = float4x4::CreateRotation(15.0f, 15.0f, 0)*triTrans.p0;
		triTrans.p1 = float4x4::CreateRotation(15.0f, 15.0f, 0) * triTrans.p1;
		triTrans.p2 = float4x4::CreateRotation(15.0f, 15.0f, 0) * triTrans.p2;

		triTrans.p0 -= 0.5;
		triTrans.p1 -= 0.5;
		triTrans.p2 -= 0.5;

		triTrans.p0.z += 3.0f;
		triTrans.p1.z += 3.0f;
		triTrans.p2.z += 3.0f;

		triProj.p0 = matProj * triTrans.p0;
		triProj.p1 = matProj * triTrans.p1;
		triProj.p2 = matProj * triTrans.p2;

		triProj.p0 += float3(1, 1, 0);
		triProj.p1 += float3(1, 1, 0);
		triProj.p2 += float3(1, 1, 0);
		triProj.p0.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p0.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
		triProj.p1.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p1.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);
		triProj.p2.x *= 0.5f * static_cast<float>(APP_VIRTUAL_WIDTH);
		triProj.p2.y *= 0.5f * static_cast<float>(APP_VIRTUAL_HEIGHT);

		App::DrawLine(
			triProj.p0.x, triProj.p0.y,
			triProj.p1.x, triProj.p1.y
		);
		App::DrawLine(
			triProj.p1.x, triProj.p1.y,
			triProj.p2.x, triProj.p2.y
		);
		App::DrawLine(
			triProj.p2.x, triProj.p2.y,
			triProj.p0.x, triProj.p0.y
		);
	}
}
