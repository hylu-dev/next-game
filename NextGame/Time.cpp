#include "stdafx.h"
#include "Time.h"

void Time::Initialize() {
}

void Time::Update(float frameTime) {
	deltaTime = frameTime;
	elapsedSeconds += frameTime;
}

void Time::Destroy() {
}
