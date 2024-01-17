#pragma once
#include "TimingFunction.h"
#include "Animator.h"

class Animation {
private:
	float3& source;
	float3 start;
	float3 end;
	float duration = 0.0f;
	float progress = 0.0f;
	TimingFunction* interpolator = nullptr;
	Animator* animator = nullptr;

public:
	Animation(float3& _start, float3 _end, float _duration, TimingFunction* _inter, Animator* _animator) :
		start(_start), end(_end), duration(_duration), interpolator(_inter), animator(_animator), source(_start) {};
	~Animation() { delete interpolator; }

	void Update();
};

