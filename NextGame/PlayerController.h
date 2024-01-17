#pragma once
#include "Component.h"
#include "Animator.h"

class PlayerController : public Component {
    float speed = 10.0f;
    Animator* animator = nullptr;
    bool minusPressed = false;
    bool plusPressed = false;

    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

