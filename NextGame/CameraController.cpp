#include "stdafx.h"
#include "CameraController.h"
#include <string>

void CameraController::Initialize() {
	animator = parentEntity->AddComponent<Animator>();
}

void CameraController::Update() {
	Camera* camera = Scene::Get().GetCamera();
	float speed = 70.0f * Time::Get().DeltaTime();

	if (App::IsKeyPressed(VK_RETURN)) {
		animator->Animate(camera->transform.position, float3(0, 0, -100.0f), 1.0f, new EaseIn());
		animator->Animate(camera->transform.rotation, 0, 1.0f, new EaseIn());
	}
	if (App::IsKeyPressed(VK_CONTROL)) {
		speed *= 2;
	}

	// Movement
	float3 movement = float3::Zero;
	float3 forward = camera->Forward();
	float3 up = float3(0, 1, 0);
	float3 pitchedUp = up - forward * up.Dot(forward);
	float3 right = up.Cross(forward);

	if (App::IsKeyPressed('A')) {
		movement -= right * speed;
	}
	if (App::IsKeyPressed('D')) {
		movement += right * speed;
	}
	if (App::IsKeyPressed('W')) {
		movement += forward * speed;
	}
	if (App::IsKeyPressed('S')) {
		movement -= forward * speed;
	}
	camera->transform.position += movement;

	if (App::IsKeyPressed(VK_SPACE)) {
		camera->transform.position.y += speed;
	}
	if (App::IsKeyPressed(VK_LSHIFT)) {
		camera->transform.position.y -= speed;
	}
	// Translation
	if (App::IsKeyPressed(VK_LEFT)) {
		camera->transform.rotation.y += speed;
	}
	if (App::IsKeyPressed(VK_RIGHT)) {
		camera->transform.rotation.y -= speed;
	}
	if (App::IsKeyPressed(VK_UP)) {
		camera->transform.rotation.x += speed;
	}
	if (App::IsKeyPressed(VK_DOWN)) {
		camera->transform.rotation.x -= speed;
	}
}

void CameraController::Destroy() {

}
