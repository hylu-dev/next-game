#pragma once
#include "TimingFunction.h"
#include "Animator.h"
#include <functional>

class Animation {
private:
	bool pause = false;
	float3& source;
	float3 start;
	float3 end;
	float duration = 0.0f;
	float progress = 0.0f;
	TimingFunction* interpolator = nullptr;
	Animator* animator = nullptr;
	std::function<void()> callback = nullptr;

public:
	Animation(float3& _start, float3 _end, float _duration, TimingFunction* _inter, Animator* _animator, std::function<void()> _callback) :
		start(_start), end(_end), duration(_duration), interpolator(_inter), animator(_animator), source(_start), callback(_callback) {};
	~Animation() { delete interpolator; }

	void Update();

	void Cancel() { progress = 1.0f; }
	void Pause() { pause = true; }
	void Resume() { pause = false; }
};

