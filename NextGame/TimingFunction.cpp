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

float ElasticEaseOut::Interpolate(float start, float end, float t) {
    const float c4 = (2 * 3.14159) / 3.0;
    float ease = sin(-13 * c4 * (t + 1)) * pow(2, -10 * t) + 1;
    return start + (end - start) * ease;
}

float3 ElasticEaseOut::Interpolate(float3 start, float3 end, float t) {
    const float c4 = (2 * 3.14159) / 3.0;
    float ease = sin(-13 * c4 * (t + 1)) * pow(2, -10 * t) + 1;
    return start + (end - start) * ease;    
}

float EaseInOutBack::Interpolate(float start, float end, float t) {
    const float c1 = 1.70158;
    const float c2 = c1 * 1.525;
    t = t * 2;
    if (t < 1) {
        return start + (end - start) * 0.5 * (t * t * ((c2 + 1) * t - c2));
    }
    t -= 2;
    return start + (end - start) * 0.5 * (t * t * ((c2 + 1) * t + c2) + 2);
}

float3 EaseInOutBack::Interpolate(float3 start, float3 end, float t) {
    const float c1 = 1.70158;
    const float c2 = c1 * 1.525;
    t = t * 2;
    if (t < 1) {
        return start + (end - start) * 0.5 * (t * t * ((c2 + 1) * t - c2));
    }
    t -= 2;
    return start + (end - start) * 0.5 * (t * t * ((c2 + 1) * t + c2) + 2);
}

float Linear::Interpolate(float start, float end, float t) {
    return start + (end - start) * t;
}

float3 Linear::Interpolate(float3 start, float3 end, float t) {
    return start + (end - start) * t;
}
