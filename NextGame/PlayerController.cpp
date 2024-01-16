#include "stdafx.h"
#include "PlayerController.h"

void PlayerController::Initialize() {
}

void PlayerController::Update() {
	float3& position = parentEntity->GetTransform().position;
	float speed = 50.0f * Time::Get().DeltaTime();

	if (App::IsKeyPressed(VK_LSHIFT)) {
		speed *= 2;
	}

	if (App::IsKeyPressed('F')) {
		position.x -= speed;
	}
	if (App::IsKeyPressed('H')) {
		position.x += speed;
	}
	if (App::IsKeyPressed('T')) {
		position.y += speed;
	}
	if (App::IsKeyPressed('G')) {
		position.y -= speed;
	}
}

void PlayerController::Destroy() {
}
