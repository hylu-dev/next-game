#pragma once
#include "Component.h"

class PlayerController : public Component {
    float speed = 10.0f;

    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

