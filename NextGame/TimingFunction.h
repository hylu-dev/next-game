#pragma once

class TimingFunction {
public:
	virtual float Interpolate(float start, float end, float t) = 0;
	virtual float3 Interpolate(float3 start, float3 end, float t) = 0;
};

class EaseIn : public TimingFunction {
	float Interpolate(float start, float end, float t) override;
	float3 Interpolate(float3 start3, float3 end, float t) override;
};

class EaseOut : public TimingFunction {
	float Interpolate(float start, float end, float t) override;
	float3 Interpolate(float3 start3, float3 end, float t) override;
};

class EaseInOut : public TimingFunction {
	float Interpolate(float start, float end, float t) override;
	float3 Interpolate(float3 start3, float3 end, float t) override;
};

class Linear : public TimingFunction {
	float Interpolate(float start, float end, float t) override;
	float3 Interpolate(float3 start3, float3 end, float t) override;
};
