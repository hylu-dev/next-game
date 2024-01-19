#include "stdafx.h"
#include "Animation.h"

void Animation::Update() {
	if (progress < 1) {
		source = interpolator->Interpolate(start, end, progress);
		progress += Time::Get().DeltaTime()/duration;
	}
	else {
		animator->RemoveAnimation(this);
	}
}
