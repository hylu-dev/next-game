#pragma once
#include "Component.h"
#include "Animator.h"

class CameraController : public Component {
    Animator* animator = nullptr;

    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

