#pragma once
#include "Component.h"
#include "TimingFunction.h"
#include <functional>

class Animation;

class Animator : public Component {
private:
	friend Animation;
	std::list<Animation*> animations;
	std::list<Animation*> animationsToDelete;

	void RemoveAnimation(Animation* ani) { animationsToDelete.push_back(ani); }

public:
	void Initialize() override;

	void Update() override;

	void Destroy() override;

	void ClearAnimations();

	Animation* Animate(float3& start, float3 end, float duration, TimingFunction* interpolator, std::function<void()> callback = nullptr, float delay = 0);
};

