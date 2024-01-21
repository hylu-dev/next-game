#pragma once
#include "ObservableComponent.h"
#include "Animator.h"
#include "ParticleEmitter.h"
#include "MeshFilter.h"

class Ship : public ObservableComponent {
public:
	bool active = false;
	int health = 100;
	float fuel = 100;
	const float fuelDrain = 4.0f;
	int scrap = 0;
	bool bulletLoaded = true;

	int multishot = 1;
	float maxSpeed = 50.0f;
	float speed = 1.0f;
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
	ParticleEmitter* hurtEmitter = nullptr;

	bool isPressed = false;

private:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void MovementHandler();

public:
	void Hurt();

	void SetColor(float3 color);

	void Upgrade();

	void FireWeapon();

	void Reload() { bulletLoaded = true; }

	float3 GetOffsetCamera();
};

