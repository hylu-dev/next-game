#pragma once
#include "Component.h"
class CameraController : public Component {
    void Initialize() override;

    void Update() override;

    void Destroy() override;
};

