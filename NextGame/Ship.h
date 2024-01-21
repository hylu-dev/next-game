#pragma once
#include "Component.h"
#include "Animator.h"
#include "ParticleEmitter.h"
#include "MeshFilter.h"

class Ship : public Component {
public:
	bool active = false;
	int health = 100;
	float fuel = 100;
	const float fuelDrain = 4.0f;
	int scrap = 0;
	bool bulletLoaded = true;

	int multishot = 1;
	float speed = 50.0f;
	float acceleration = 2.0f;
	float3 movement = float3::Zero;
	float3 rotationSpeed = float3::Zero;
	float friction = 2.0f;

	Camera* camera;
	float cameraZOffset = -20;	
	float cameraYOffset = 5;

	float3 forward = { 0,0,1 };
	// Components
	MeshFilter* meshFilter = nullptr;
	Animator* animator = nullptr;
	ParticleEmitter* trailEmitter = nullptr;
	ParticleEmitter* bulletEmitter = nullptr;

private:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void MovementHandler();

public:

	void FireWeapon();

	float3 GetOffsetCamera();
};

