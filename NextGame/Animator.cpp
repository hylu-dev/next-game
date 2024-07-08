#include "stdafx.h"
#include "Animation.h"

void Animator::Initialize() {

}

void Animator::Update() {
	for (auto& ani : animations) {
		ani->Update();
	}

	for (auto& ani : animationsToDelete) {
		animations.remove(ani);
		delete ani;
		ani = nullptr;
	}
	animationsToDelete.clear();
}

void Animator::Destroy() {
	for (auto& ani : animations) {
		delete ani;
		ani = nullptr;
	}
	animations.clear();
	animationsToDelete.clear();
}

void Animator::ClearAnimations() {
	for (auto& ani : animations) {
		ani->Cancel();
	}
}

Animation* Animator::Animate(float3& start, float3 end, float duration, TimingFunction* interpolator, std::function<void()> callback, float delay) {
	Animation* anim = new Animation(start, end, duration, interpolator, this, callback, delay);
	animations.push_back(anim);
	return anim;
}