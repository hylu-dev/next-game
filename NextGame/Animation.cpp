#include "stdafx.h"
#include "Animation.h"

void Animation::Update() {
	if (progress < 1) {
		source = interpolator->Interpolate(start, end, progress);
		progress += Time::Get().DeltaTime()/duration;
	}
	else {
		if (callback != nullptr) {
			callback();
		}
		animator->RemoveAnimation(this);
	}
}
