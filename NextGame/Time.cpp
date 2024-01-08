#include "stdafx.h"
#include "Time.h"

void Time::Initialize() {
	beginTime = std::chrono::system_clock().now();
	endTime = std::chrono::system_clock().now();
	deltaTime = std::chrono::duration<float>(0);
	elapsedSeconds = std::chrono::duration<float>(0);
}

void Time::Update() {
	endTime = std::chrono::system_clock().now();
	deltaTime = endTime - beginTime;
	beginTime = endTime;
	elapsedSeconds += deltaTime;
}

void Time::Destroy() {
}
