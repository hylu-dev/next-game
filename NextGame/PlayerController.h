#pragma once
#include "Component.h"
#include "Animator.h"
#include "ParticleEmitter.h"

class PlayerController : public Component {
    float speed = 1.0f;
    float3 direction;
    Animator* animator = nullptr;
    ParticleEmitter* emitter = nullptr;

    bool minusPressed = false;
    bool plusPressed = false;

    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

