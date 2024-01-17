#include "stdafx.h"
#include "Animation.h"

void Animation::Update() {
	Time::Get().temp = progress;
	if (progress < 1) {
		source = interpolator->Interpolate(start, end, progress);
		progress += Time::Get().DeltaTime()/duration;
	}
	else {
		Time::Get().temp = 100.0f;
		animator->RemoveAnimation(this);
	}
}
