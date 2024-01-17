#include "stdafx.h"
#include "TimingFunction.h"

float EaseIn::Interpolate(float start, float end, float t) {
    return start + (end - start) * (t * t * t);
}

float3 EaseIn::Interpolate(float3 start, float3 end, float t) {
    return start + (end - start) * (t * t * t);
}


float EaseOut::Interpolate(float start, float end, float t) {
    return start + (end - start) * (1 - std::pow(1 - t, 2));
}

float3 EaseOut::Interpolate(float3 start, float3 end, float t) {
    return start + (end - start) * (1 - std::pow(1 - t, 2));
}

float EaseInOut::Interpolate(float start, float end, float t) {
    return start + (end - start) * ((t < 0.5) ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2);
}

float3 EaseInOut::Interpolate(float3 start, float3 end, float t) {
    return start + (end - start) * ((t < 0.5) ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2);
}

float Linear::Interpolate(float start, float end, float t) {
    return 0.0f;
}

float3 Linear::Interpolate(float3 start, float3 end, float t) {
    return start + (end - start) * t;
}
