//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app\app.h"

#include "Mesh.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	float4x4 m1 = float4x4::CreateRotation(0,0,180);
	float4x4 m2 = float4x4::CreateTranslation(float3::One);
	float4x4 transform = m2*m1;

	float3 position = float3(1, 0, 0);
	//position = m1 * position;
	//position = m2 * position;
	position = transform * position;
	//------------------------------------------------------------------------

	Mesh* cube = new Mesh();
	cube->Initialize();
	cube->LoadMesh();
	Renderer::Get().Initialize();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	Renderer::Get().Update();

	/*App::Print(100, 100, "Sample Text");

	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}*/
}

void Shutdown()
{	

}