#pragma once
#include "Component.h"

class PlayerController : public Component {
    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

